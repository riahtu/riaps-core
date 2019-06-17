//
// Created by istvan on 1/24/19.
//

#include <framework/rfw_security.h>
#include <experimental/filesystem>
#include <fstream>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

using namespace std;

namespace fs = experimental::filesystem;

namespace riaps {
    namespace framework {
        const bool Security::HasSecurity() {
            INIReader reader(CONF_PATH);

            if (reader.ParseError() != 0) {
                return false;
            }

            string security = reader.Get("RIAPS", "security", "off");
            if (security == "on" ||
                security == "True")
                return true;

            return false;
        }

        std::shared_ptr<dht::crypto::PrivateKey> Security::private_key() {
            ifstream privfs;
            privfs.open(key_path(), ios::ate);
            if (!privfs.good())
                return nullptr;
            auto pos = privfs.tellg();
            vector<uint8_t> buffer(pos);
            privfs.seekg(0, ios::beg);
            privfs.read((char*)buffer.begin().base(), pos);
            return make_shared<dht::crypto::PrivateKey>(buffer);
        }

        const std::string Security::key_path() {
            fs::path key_path(KEY_FOLDER);
            key_path /= KEY_FILE;

            return key_path.string();
        }

        zcert_t* Security::curve_key() {
            auto result = zcert_load(curve_key_path().c_str());
            return result;
        }

        const std::string Security::curve_key_path() {
            fs::path key_path(CURVE_FOLDER);
            key_path /= CURVE_KEY;
            return key_path.string();
        }

    }
}
