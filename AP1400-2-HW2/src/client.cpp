#include "client.h"


Client::Client(std::string id, const Server& server) : id(id), server(&server){
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id() {
    return id;
}

std::string Client::get_publickey() const {
    return public_key;
}

double Client::get_wallet() {
    return server->get_wallet(get_id());
}

std::string Client::sign(std::string txt) const {
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) {
    auto sender = get_id();
    if (server->get_client(receiver) == nullptr || value <= 0) {
        return false;
    }
    std::string trx = sender + '-' + receiver + '-' + std::to_string(value);
    std::string signature = sign(trx);
    return server->add_pending_trx(trx, signature);
}

size_t Client::generate_nonce() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1000, 9999);
    return dis(gen);
}


