#include "server.h"

std::vector<std::string> pending_trxs;
Server::Server() {}

std::shared_ptr<Client> Server::add_client(std::string id)
{
    while (get_client(id) != nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1000, 9999);
        int ed = dis(gen);
        id += std::to_string(ed);
    }
    std::cout << id << std::endl;
    std::shared_ptr<Client> ptr_c(new Client(id, *this));
    clients[ptr_c] = 5.0;
    return ptr_c;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
    for (auto &client : clients) {
        auto c = client.first;
        if (c->get_id() == id) {
            return c;
        }
    }
    // std::cout << "no client" << std::endl;
    return nullptr;
}

double Server::get_wallet(std::string id) const {
    for (auto &client : clients) {
        auto c = client.first;
        if (c->get_id() == id) {
            return client.second;
        }
    }
    std::cout << "no client" << std::endl;
    return 0;    
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    size_t st = 0;
    size_t ed = trx.find('-');
    if (ed != std::string::npos) {
        sender = trx.substr(st, ed - st);
        st = ed + 1;
    } else {
        throw std::runtime_error("incorrect trx!");
    }
    ed = trx.find('-', st);
    if (ed != std::string::npos) {
        receiver = trx.substr(st, ed - st);
        st = ed + 1;
    } else {
        throw std::runtime_error("incorrect trx!");
    }
    ed = trx.find('-', st);
    if (ed != std::string::npos) {
        throw std::runtime_error("incorrect trx!");
    }
    value = std::stod(trx.substr(st));
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const {
    std::string sender, receiver;
    double value;
    parse_trx(trx, sender, receiver, value);
    auto sender_ptr = get_client(sender);
    std::string public_key = sender_ptr->get_publickey();
    bool authentic = crypto::verifySignature(public_key, trx, signature);
    if (authentic && get_wallet(sender) >= value) {
        pending_trxs.push_back(trx);
        return true;
    } else {
        std::cout << "incorrect!" << std::endl;
        return false;
    }
}

size_t Server::mine() {
    std::string mempool{};
    for(const auto& trx : pending_trxs)
        mempool += trx;  
    while(1) {
        for(auto& client : clients) {
            auto client_ptr = client.first;
            size_t nonce = client_ptr->generate_nonce();
            std::string q = mempool + std::to_string(nonce);
            std::string ans = crypto::sha256(q).substr(0,3);
            if (ans == "000") {
                client.second += 6.25;
                for(const auto& trx : pending_trxs) {
                    std::string sender, receiver;
                    double value;
                    parse_trx(trx, sender, receiver, value);
                    clients[get_client(sender)] -= value;
                    clients[get_client(receiver)] += value;
                }
                pending_trxs.clear();
                return nonce;
            }
        }
    }  
}



void  show_wallets(const  Server& server)
{
	std::cout << std::string(20, '*') << std::endl;
	for(const auto& client: server.clients)
		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
	std::cout << std::string(20, '*') << std::endl;
}
