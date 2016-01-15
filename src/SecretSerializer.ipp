

namespace BitCrypto{


template<class Encoder>
SecretSerializer<Encoder>::SecretSerializer()
{}


template<class Encoder>
SecretSerializer<Encoder>::SecretSerializer(const Secp256k1ContextPtr &context) : 
    _context(context)
{}


template<class Encoder>
std::string SecretSerializer<Encoder>::serialize(const Secret &secret) const 
{
    Encoder encoder;
    return encoder.encode(secret.begin(), secret.end());
}


template<class Encoder>
template<class Cipher>
std::string SecretSerializer<Encoder>::serialize(const SecuredSecret<Cipher> &secret) const
{
    Encoder encoder;
    const Data & secretData = secret.getData();
    return encoder.encode(secretData.begin(), secretData.end());
}


template<class Encoder>
template<class Cipher>
SecuredSecret<Cipher> SecretSerializer<Encoder>::unserialize(const std::string &serialized, const Cipher &cipher) const
{
    SecuredSecret<Cipher> secret(_context, cipher);
    Encoder encoder;
    encoder.decode(serialized.begin(), serialized.end(), secret.getData());
    return secret;
}


template<class Encoder>
Secret SecretSerializer<Encoder>::unserialize(const std::string &serialized) const
{
    Encoder encoder;
    Data data = encoder.decode(serialized.begin(), serialized.end());
    if(data.size() != 32)
    {
        throw std::runtime_error("Invalid serialized secret");
    }
    Secret secret(_context);
    std::copy(data.begin(), data.end(), secret.begin());
    return secret;
}

}
