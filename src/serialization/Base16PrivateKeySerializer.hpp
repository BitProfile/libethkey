#pragma once 

#include "detail/GenericPrivateKeySerializer.hpp"
#include "ethkey/encoding/Base16Encoder.hpp"


namespace Ethereum{


typedef GenericPrivateKeySerializer<Base16Encoder> Base16PrivateKeySerializer;


}
