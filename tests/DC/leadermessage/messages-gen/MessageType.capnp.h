// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: MessageType.capnp

#ifndef CAPNP_INCLUDED_a15e3a45b1cda517_
#define CAPNP_INCLUDED_a15e3a45b1cda517_

#include <capnp/generated-header-support.h>

#if CAPNP_VERSION != 5003
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(b350bf06f720699e);

}  // namespace schemas
}  // namespace capnp


struct MessageType {
  MessageType() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(b350bf06f720699e, 0, 1)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand = &schema->defaultBrand;
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class MessageType::Reader {
public:
  typedef MessageType Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand);
  }
#endif  // !CAPNP_LITE

  inline bool hasMsg() const;
  inline  ::capnp::Text::Reader getMsg() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class MessageType::Builder {
public:
  typedef MessageType Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline bool hasMsg();
  inline  ::capnp::Text::Builder getMsg();
  inline void setMsg( ::capnp::Text::Reader value);
  inline  ::capnp::Text::Builder initMsg(unsigned int size);
  inline void adoptMsg(::capnp::Orphan< ::capnp::Text>&& value);
  inline ::capnp::Orphan< ::capnp::Text> disownMsg();

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class MessageType::Pipeline {
public:
  typedef MessageType Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

inline bool MessageType::Reader::hasMsg() const {
  return !_reader.getPointerField(0 * ::capnp::POINTERS).isNull();
}
inline bool MessageType::Builder::hasMsg() {
  return !_builder.getPointerField(0 * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader MessageType::Reader::getMsg() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(
      _reader.getPointerField(0 * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder MessageType::Builder::getMsg() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(
      _builder.getPointerField(0 * ::capnp::POINTERS));
}
inline void MessageType::Builder::setMsg( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(
      _builder.getPointerField(0 * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder MessageType::Builder::initMsg(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(
      _builder.getPointerField(0 * ::capnp::POINTERS), size);
}
inline void MessageType::Builder::adoptMsg(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(
      _builder.getPointerField(0 * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> MessageType::Builder::disownMsg() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(
      _builder.getPointerField(0 * ::capnp::POINTERS));
}


#endif  // CAPNP_INCLUDED_a15e3a45b1cda517_
