/*
 *  Copyright (C) 2014-2016 Savoir-faire Linux Inc.
 *  Author(s) : Adrien Béraud <adrien.beraud@savoirfairelinux.com>
 *              Simon Désaulniers <sim.desaulniers@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "infohash.h"
#include "value.h"
#include "utils.h"
#include "network_engine.h"
#include "scheduler.h"
#include "routing_table.h"
#include "callbacks.h"
#include "log_enable.h"

#include <string>
#include <array>
#include <vector>
#include <map>
#include <functional>
#include <memory>

#ifdef _WIN32
#include <iso646.h>
#endif

namespace dht {

namespace net {
struct Request;
} /* namespace net */

/**
 * Main Dht class.
 * Provides a Distributed Hash Table node.
 *
 * Must be given open UDP sockets and ::periodic must be
 * called regularly.
 */
class OPENDHT_PUBLIC Dht {
public:

    // [[deprecated]]
    using NodeExport = dht::NodeExport;

    // [[deprecated]]
    using Status = NodeStatus;

    Dht();

    /**
     * Initialise the Dht with two open sockets (for IPv4 and IP6)
     * and an ID for the node.
     */
    Dht(int s, int s6, Config config);
    virtual ~Dht();

    /**
     * Get the ID of the node.
     */
    inline const InfoHash& getNodeId() const { return myid; }

    /**
     * Get the current status of the node for the given family.
     */
    NodeStatus getStatus(sa_family_t af) const;

    NodeStatus getStatus() const {
        return std::max(getStatus(AF_INET), getStatus(AF_INET6));
    }

    /**
     * Performs final operations before quitting.
     */
    void shutdown(ShutdownCallback cb);

    /**
     * Returns true if the node is running (have access to an open socket).
     *
     *  af: address family. If non-zero, will return true if the node
     *      is running for the provided family.
     */
    bool isRunning(sa_family_t af = 0) const;

    /**
     * Enable or disable logging of DHT internal messages
     */
    void setLoggers(LogMethod error = NOLOG, LogMethod warn = NOLOG, LogMethod debug = NOLOG);

    /**
     * Only print logs related to the given InfoHash (if given), or disable filter (if zeroes).
     */
    void setLogFilter(const InfoHash& f) {
        DHT_LOG.setFilter(f);
    }

    virtual void registerType(const ValueType& type) {
        types[type.id] = type;
    }
    const ValueType& getType(ValueType::Id type_id) const {
        const auto& t_it = types.find(type_id);
        return (t_it == types.end()) ? ValueType::USER_DATA : t_it->second;
    }

    /**
     * Insert a node in the main routing table.
     * The node is not pinged, so this should be
     * used to bootstrap efficiently from previously known nodes.
     */
    void insertNode(const InfoHash& id, const SockAddr&);
    void insertNode(const InfoHash& id, const sockaddr* sa, socklen_t salen) {
        insertNode(id, SockAddr(sa, salen));
    }
    void insertNode(const NodeExport& n) {
        insertNode(n.id, SockAddr(n.ss, n.sslen));
    }

    void pingNode(const sockaddr*, socklen_t, DoneCallbackSimple&& cb={});

    time_point periodic(const uint8_t *buf, size_t buflen, const SockAddr&);
    time_point periodic(const uint8_t *buf, size_t buflen, const sockaddr* from, socklen_t fromlen) {
        return periodic(buf, buflen, SockAddr(from, fromlen));
    }

    /**
     * Get a value by searching on all available protocols (IPv4, IPv6),
     * and call the provided get callback when values are found at key.
     * The operation will start as soon as the node is connected to the network.
     * @param cb a function called when new values are found on the network.
     *           It should return false to stop the operation.
     * @param donecb a function called when the operation is complete.
                     cb and donecb won't be called again afterward.
     * @param f a filter function used to prefilter values.
     */
    virtual void get(const InfoHash& key, GetCallback cb, DoneCallback donecb={}, Value::Filter&& f={}, Where&& w = {});
    virtual void get(const InfoHash& key, GetCallback cb, DoneCallbackSimple donecb={}, Value::Filter&& f={}, Where&& w = {}) {
        get(key, cb, bindDoneCb(donecb), std::forward<Value::Filter>(f), std::forward<Where>(w));
    }
    virtual void get(const InfoHash& key, GetCallbackSimple cb, DoneCallback donecb={}, Value::Filter&& f={}, Where&& w = {}) {
        get(key, bindGetCb(cb), donecb, std::forward<Value::Filter>(f), std::forward<Where>(w));
    }
    virtual void get(const InfoHash& key, GetCallbackSimple cb, DoneCallbackSimple donecb, Value::Filter&& f={}, Where&& w = {}) {
        get(key, bindGetCb(cb), bindDoneCb(donecb), std::forward<Value::Filter>(f), std::forward<Where>(w));
    }
    /**
     * Similar to Dht::get, but sends a Query to filter data remotely.
     * @param key the key for which to query data for.
     * @param cb a function called when new values are found on the network.
     *           It should return false to stop the operation.
     * @param donecb a function called when the operation is complete.
                     cb and donecb won't be called again afterward.
     * @param q a query used to filter values on the remotes before they send a
     *          response.
     */
    virtual void query(const InfoHash& key, QueryCallback cb, DoneCallback done_cb = {}, Query&& q = {});
    virtual void query(const InfoHash& key, QueryCallback cb, DoneCallbackSimple done_cb = {}, Query&& q = {}) {
        query(key, cb, bindDoneCb(done_cb), std::forward<Query>(q));
    }

    /**
     * Get locally stored data for the given hash.
     */
    std::vector<std::shared_ptr<Value>> getLocal(const InfoHash& key, Value::Filter f = Value::AllFilter()) const;

    /**
     * Get locally stored data for the given key and value id.
     */
    std::shared_ptr<Value> getLocalById(const InfoHash& key, Value::Id vid) const;

    /**
     * Announce a value on all available protocols (IPv4, IPv6).
     *
     * The operation will start as soon as the node is connected to the network.
     * The done callback will be called once, when the first announce succeeds, or fails.
     */
    void put(const InfoHash& key,
            std::shared_ptr<Value>,
            DoneCallback cb=nullptr,
            time_point created=time_point::max(),
            bool permanent = false);
    void put(const InfoHash& key,
            const std::shared_ptr<Value>& v,
            DoneCallbackSimple cb,
            time_point created=time_point::max(),
            bool permanent = false)
    {
        put(key, v, bindDoneCb(cb), created, permanent);
    }

    void put(const InfoHash& key,
            Value&& v,
            DoneCallback cb=nullptr,
            time_point created=time_point::max(),
            bool permanent = false)
    {
        put(key, std::make_shared<Value>(std::move(v)), cb, created, permanent);
    }
    void put(const InfoHash& key,
            Value&& v,
            DoneCallbackSimple cb,
            time_point created=time_point::max(),
            bool permanent = false)
    {
        put(key, std::forward<Value>(v), bindDoneCb(cb), created, permanent);
    }

    /**
     * Get data currently being put at the given hash.
     */
    std::vector<std::shared_ptr<Value>> getPut(const InfoHash&);

    /**
     * Get data currently being put at the given hash with the given id.
     */
    std::shared_ptr<Value> getPut(const InfoHash&, const Value::Id&);

    /**
     * Stop any put/announce operation at the given location,
     * for the value with the given id.
     */
    bool cancelPut(const InfoHash&, const Value::Id&);

    /**
     * Listen on the network for any changes involving a specified hash.
     * The node will register to receive updates from relevent nodes when
     * new values are added or removed.
     *
     * @return a token to cancel the listener later.
     */
    virtual size_t listen(const InfoHash&, GetCallback, Value::Filter&&={}, Where&& w = {});
    virtual size_t listen(const InfoHash& key, GetCallbackSimple cb, Value::Filter f={}, Where w = {}) {
        return listen(key, bindGetCb(cb), std::forward<Value::Filter>(f), std::forward<Where>(w));
    }

    virtual bool cancelListen(const InfoHash&, size_t token);

    /**
     * Inform the DHT of lower-layer connectivity changes.
     * This will cause the DHT to assume a public IP address change.
     * The DHT will recontact neighbor nodes, re-register for listen ops etc.
     */
    void connectivityChanged(sa_family_t);
    void connectivityChanged() {
        reported_addr.clear();
        connectivityChanged(AF_INET);
        connectivityChanged(AF_INET6);
    }

    /**
     * Get the list of good nodes for local storage saving purposes
     * The list is ordered to minimize the back-to-work delay.
     */
    std::vector<NodeExport> exportNodes();

    std::vector<ValuesExport> exportValues() const;
    void importValues(const std::vector<ValuesExport>&);

    unsigned getNodesStats(sa_family_t af, unsigned *good_return, unsigned *dubious_return, unsigned *cached_return,
            unsigned *incoming_return) const;
    std::string getStorageLog() const;
    std::string getStorageLog(const InfoHash&) const;

    std::string getRoutingTablesLog(sa_family_t) const;
    std::string getSearchesLog(sa_family_t) const;
    std::string getSearchLog(const InfoHash&, sa_family_t af = AF_UNSPEC) const;

    void dumpTables() const;
    std::vector<unsigned> getNodeMessageStats(bool in = false) {
        return network_engine.getNodeMessageStats(in);
    }

    /**
     * Set the in-memory storage limit in bytes
     */
    void setStorageLimit(size_t limit = DEFAULT_STORAGE_LIMIT) {
        max_store_size = limit;
    }

    /**
     * Returns the total memory usage of stored values and the number
     * of stored values.
     */
    std::pair<size_t, size_t> getStoreSize() const {
        return {total_store_size, total_values};
    }

    std::vector<SockAddr> getPublicAddress(sa_family_t family = 0);

protected:
    Logger DHT_LOG;
    bool logFilerEnable_ {};
    InfoHash logFiler_ {};

private:

    /* When performing a search, we search for up to SEARCH_NODES closest nodes
       to the destination, and use the additional ones to backtrack if any of
       the target 8 turn out to be dead. */
    static constexpr unsigned SEARCH_NODES {14};

    /* The number of bad nodes is limited in order to help determine
     * presence of connectivity changes. See
     * https://github.com/savoirfairelinux/opendht/issues/137 for details.
     *
     * According to the tables, 25 is a good average value for big networks. If
     * the network is small, normal search expiration process will handle the
     * situation.
     * */
    static constexpr unsigned SEARCH_MAX_BAD_NODES {25};

    /* Concurrent search nodes requested count */
    static constexpr unsigned MAX_REQUESTED_SEARCH_NODES {4};

    /* Number of listening nodes */
    static constexpr unsigned LISTEN_NODES {4};

    /* The maximum number of values we store for a given hash. */
    static constexpr unsigned MAX_VALUES {1024};

    /* The maximum number of hashes we're willing to track. */
    static constexpr unsigned MAX_HASHES {16384};

    /* The maximum number of searches we keep data about. */
    static constexpr unsigned MAX_SEARCHES {2048};

    static constexpr std::chrono::minutes MAX_STORAGE_MAINTENANCE_EXPIRE_TIME {10};

    /* The time after which we consider a search to be expirable. */
    static constexpr std::chrono::minutes SEARCH_EXPIRE_TIME {62};

    /* Timeout for listen */
    static constexpr std::chrono::seconds LISTEN_EXPIRE_TIME {30};

    static constexpr std::chrono::seconds REANNOUNCE_MARGIN {10};

    static constexpr size_t TOKEN_SIZE {64};

    // internal structures
    struct SearchNode;
    struct Get;
    struct Announce;
    struct LocalListener;
    struct Search;
    struct ValueStorage;
    struct Listener;
    struct Storage;

    // prevent copy
    Dht(const Dht&) = delete;
    Dht& operator=(const Dht&) = delete;

    InfoHash myid {};

    std::array<uint8_t, 8> secret {{}};
    std::array<uint8_t, 8> oldsecret {{}};

    // registred types
    std::map<ValueType::Id, ValueType> types;

    // are we a bootstrap node ?
    // note: Any running node can be used as a bootstrap node.
    //       Only nodes running only as bootstrap nodes should
    //       be put in bootstrap mode.
    const bool is_bootstrap {false};
    const bool maintain_storage {false};

    // the stuff
    RoutingTable buckets4 {};
    RoutingTable buckets6 {};

    std::map<InfoHash, Storage> store;
    size_t total_values {0};
    size_t total_store_size {0};
    size_t max_store_size {DEFAULT_STORAGE_LIMIT};

    using SearchMap = std::map<InfoHash, std::shared_ptr<Search>>;
    SearchMap searches4 {};
    SearchMap searches6 {};
    uint16_t search_id {0};

    // map a global listen token to IPv4, IPv6 specific listen tokens.
    // 0 is the invalid token.
    std::map<size_t, std::tuple<size_t, size_t, size_t>> listeners {};
    size_t listener_token {1};

    // timing
    Scheduler scheduler;
    std::shared_ptr<Scheduler::Job> nextNodesConfirmation {};
    std::shared_ptr<Scheduler::Job> nextStorageMaintenance {};
    time_point mybucket_grow_time {time_point::min()}, mybucket6_grow_time {time_point::min()};

    net::NetworkEngine network_engine;
    unsigned pending_pings4 {0};
    unsigned pending_pings6 {0};

    using ReportedAddr = std::pair<unsigned, SockAddr>;
    std::vector<ReportedAddr> reported_addr;

    void rotateSecrets();

    Blob makeToken(const sockaddr *sa, bool old) const;
    bool tokenMatch(const Blob& token, const sockaddr *sa) const;

    void reportedAddr(const SockAddr&);

    // Storage
    void storageAddListener(const InfoHash& id, const std::shared_ptr<Node>& node, size_t tid, Query&& = {});
    bool storageStore(const InfoHash& id, const std::shared_ptr<Value>& value, time_point created);
    void expireStorage();
    void storageChanged(const InfoHash& id, Storage& st, ValueStorage&);
    std::string printStorageLog(const decltype(store)::value_type&) const;

    /**
     * For a given storage, if values don't belong there anymore because this
     * node is too far from the target, values are sent to the appropriate
     * nodes.
     */
    void dataPersistence(InfoHash id);
    size_t maintainStorage(decltype(store)::value_type&, bool force=false, DoneCallback donecb=nullptr);

    // Buckets
    RoutingTable& buckets(sa_family_t af) { return af == AF_INET ? buckets4 : buckets6; }
    const RoutingTable& buckets(sa_family_t af) const { return af == AF_INET ? buckets4 : buckets6; }
    Bucket* findBucket(const InfoHash& id, sa_family_t af) {
        RoutingTable::iterator b;
        switch (af) {
        case AF_INET:
            b = buckets4.findBucket(id);
            return b == buckets4.end() ? nullptr : &(*b);
        case AF_INET6:
            b = buckets6.findBucket(id);
            return b == buckets6.end() ? nullptr : &(*b);
        default:
            return nullptr;
        }
    }
    const Bucket* findBucket(const InfoHash& id, sa_family_t af) const {
        return const_cast<Dht*>(this)->findBucket(id, af);
    }

    void expireBuckets(RoutingTable&);
    int sendCachedPing(Bucket& b);
    bool bucketMaintenance(RoutingTable&);
    void dumpBucket(const Bucket& b, std::ostream& out) const;

    // Nodes
    void onNewNode(const std::shared_ptr<Node>& node, int confirm);
    std::shared_ptr<Node> findNode(const InfoHash& id, sa_family_t af);
    const std::shared_ptr<Node> findNode(const InfoHash& id, sa_family_t af) const;
    bool trySearchInsert(const std::shared_ptr<Node>& node);

    // Searches

    inline SearchMap& searches(sa_family_t af) { return af == AF_INET ? searches4 : searches6; }
    inline const SearchMap& searches(sa_family_t af) const { return af == AF_INET ? searches4 : searches6; }

    /**
     * Low-level method that will perform a search on the DHT for the specified
     * infohash (id), using the specified IP version (IPv4 or IPv6).
     */
    std::shared_ptr<Search> search(const InfoHash& id, sa_family_t af, GetCallback = {}, QueryCallback = {}, DoneCallback = {}, Value::Filter = {}, Query q = {});

    void announce(const InfoHash& id, sa_family_t af, std::shared_ptr<Value> value, DoneCallback callback, time_point created=time_point::max(), bool permanent = false);
    size_t listenTo(const InfoHash& id, sa_family_t af, GetCallback cb, Value::Filter f = Value::AllFilter(), const std::shared_ptr<Query>& q = {});

    /**
     * Refill the search with good nodes if possible.
     *
     * @param sr  The search to refill.
     *
     * @return the number inserted nodes.
     */
    unsigned refill(Search& sr);
    void expireSearches();

    void confirmNodes();
    void expire();

    /**
     * Generic function to execute when a 'get' request has completed.
     *
     * @param status  The request passed by the network engine.
     * @param answer  The answer from the network engine.
     * @param ws      A weak pointer to the search concerned by the request.
     * @param query   The query sent to the node.
     */
    void searchNodeGetDone(const net::Request& status,
            net::NetworkEngine::RequestAnswer&& answer,
            std::weak_ptr<Search> ws,
            std::shared_ptr<Query> query);

    /**
     * Generic function to execute when a 'get' request expires.
     *
     * @param status  The request passed by the network engine.
     * @param over    Whether we're done to try sending the request to the node
     *                or not. This lets us mark a node as candidate.
     * @param ws      A weak pointer to the search concerned by the request.
     * @param query   The query sent to the node.
     */
    void searchNodeGetExpired(const net::Request& status, bool over, std::weak_ptr<Search> ws, std::shared_ptr<Query> query);

    /**
     * This method recovers sends individual request for values per id.
     *
     * @param ws     A weak pointer to the Search.
     * @param query  The initial query passed through the API.
     * @param n      The node to which send the requests.
     */
    void paginate(std::weak_ptr<Search> ws, std::shared_ptr<Query> query, SearchNode* n);

    /**
     * If update is true, this method will also send message to synced but non-updated search nodes.
     */
    SearchNode* searchSendGetValues(std::shared_ptr<Search> sr, SearchNode *n = nullptr, bool update = true);

    /**
     * Forwards an 'announce' request for a list of nodes to the network engine.
     *
     * @param sr  The search for which we want to announce a value.
     * @param announce  The 'announce' structure.
     */
    void searchSendAnnounceValue(const std::shared_ptr<Search>& sr);

    /**
     * Main process of a Search's operations. This function will demand the
     * network engine to send requests packets for all pending operations
     * ('get', 'put' and 'listen').
     *
     * @param sr  The search to execute its operations.
     */
    void searchStep(std::shared_ptr<Search> sr);
    void dumpSearch(const Search& sr, std::ostream& out) const;

    bool neighbourhoodMaintenance(RoutingTable&);

    void processMessage(const uint8_t *buf, size_t buflen, const SockAddr&);

    void onError(std::shared_ptr<net::Request> node, net::DhtProtocolException e);
    /* when our address is reported by a distant peer. */
    void onReportedAddr(const InfoHash& id, const SockAddr&);
    /* when we receive a ping request */
    net::NetworkEngine::RequestAnswer onPing(std::shared_ptr<Node> node);
    /* when we receive a "find node" request */
    net::NetworkEngine::RequestAnswer onFindNode(std::shared_ptr<Node> node, const InfoHash& hash, want_t want);
    void onFindNodeDone(const std::shared_ptr<Node>& status,
            net::NetworkEngine::RequestAnswer& a,
            std::shared_ptr<Search> sr);
    /* when we receive a "get values" request */
    net::NetworkEngine::RequestAnswer onGetValues(std::shared_ptr<Node> node,
            const InfoHash& hash,
            want_t want,
            const Query& q);
    void onGetValuesDone(const std::shared_ptr<Node>& status,
            net::NetworkEngine::RequestAnswer& a,
            std::shared_ptr<Search>& sr,
            const std::shared_ptr<Query>& orig_query);
    /* when we receive a listen request */
    net::NetworkEngine::RequestAnswer onListen(std::shared_ptr<Node> node,
            const InfoHash& hash,
            const Blob& token,
            size_t socket_id,
            const Query& query);
    void onListenDone(const std::shared_ptr<Node>& status,
            net::NetworkEngine::RequestAnswer& a,
            std::shared_ptr<Search>& sr);
    /* when we receive an announce request */
    net::NetworkEngine::RequestAnswer onAnnounce(std::shared_ptr<Node> node,
            const InfoHash& hash,
            const Blob& token,
            const std::vector<std::shared_ptr<Value>>& v,
            const time_point& created);
    net::NetworkEngine::RequestAnswer onRefresh(std::shared_ptr<Node> node,
            const InfoHash& hash,
            const Blob& token,
            const Value::Id& vid);
    void onAnnounceDone(const std::shared_ptr<Node>& status,
            net::NetworkEngine::RequestAnswer& a,
            std::shared_ptr<Search>& sr);
};

}