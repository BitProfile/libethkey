#include <iostream>

namespace Ethereum{

template<class KDF>
AesCipher<KDF>::AesCipher()
{}

template<class KDF>
AesCipher<KDF> & AesCipher<KDF>::operator = (const AesCipher &copy)
{
    _iv = copy._iv;
    _params = copy._params;
    return *this;
}

template<class KDF>
bool AesCipher<KDF>::operator == (const AesCipher &b) const
{
    return _iv == b._iv && _params == b._params;
}

template<class KDF>
template<class Handler, class Input, class Output>
bool AesCipher<KDF>::execute(Handler &handler, const Input &input, Output &output, const Data &derivedKey) const
{
    handler.SetKeyWithIV(&derivedKey, std::min(derivedKey.size(), _iv.size()), &_iv, _iv.size());
    CryptoPP::StreamTransformationFilter stream(handler, NULL);
    for(typename Input::const_iterator it = input.begin(), end=input.end(); it!=end; ++it)
    {
        stream.Put(*it);
    }
    output.resize(stream.MaxRetrievable());
    stream.Get(BufferCast(output), output.size());
    return true;
}


template<class KDF>
template<class Input>
bool AesCipher<KDF>::encrypt(const Input &input, EncryptedData &output, const std::string &password) const
{
    Data derivedKey = makeDerived(password);

    CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption encryption;
    if(!execute(encryption, input, output.data, derivedKey))
    {
        return false;
    }

    CipherMacFactory macFactory;
    macFactory.createMac(output.data, derivedKey, output.mac);

    return true;
}


template<class KDF>
template<class Output>
bool AesCipher<KDF>::decrypt(const EncryptedData &input, Output &output, const std::string &password) const
{
    Data derivedKey = makeDerived(password);
    Data mac;
    CipherMacFactory macFactory;
    macFactory.createMac(input.data, derivedKey, mac);

    if(mac!=input.mac)
    {
        return false;
    }

    CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decryption;
    if(!execute(decryption, input.data, output, derivedKey))
    {
        return false;
    }

    return true;
}



template<class KDF>
template<class Input>
EncryptedData AesCipher<KDF>::encrypt(const Input &input, const std::string &password) const
{
    EncryptedData output;
    if(!encrypt(input, output, password))
    {
        throw std::runtime_error("failed to encrypt");
    }
    return output;
}


template<class KDF>
template<class Output>
Output AesCipher<KDF>::decrypt(const EncryptedData &input, const std::string &password) const
{
    Output output;
    if(!decrypt(input, output, password))
    {
        throw std::runtime_error("invalid password");
    }
    return output;
}

template<class KDF>
AesCipher<KDF>::AesCipher(const Data &iv, const typename KDF::Params &params) : 
    _iv(iv),
    _params(params)
{}

template<class KDF>
const typename AesCipher<KDF>::KdfParams & AesCipher<KDF>::getParams() const
{
    return _params;
}

template<class KDF>
const Data & AesCipher<KDF>::getIV() const
{
    return _iv;
}



template<class KDF>
Data AesCipher<KDF>::decrypt(const EncryptedData &input, const std::string &password) const
{
    return decrypt<Data>(input, password);
}


template<class KDF>
Data AesCipher<KDF>::makeDerived(const std::string &password) const
{
    DerivedKeyFactory keyFactory;
    return keyFactory.makeDerived(password, _params);
}





}
