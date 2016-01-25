#pragma once 

#include "detail/GenericPublicKeySerializer.hpp"
#include "ethkey/encoding/Base58Encoder.hpp"

namespace Ethereum{


typedef GenericPublicKeySerializer<Base58Encoder> Base58PublicKeySerializer;


}
