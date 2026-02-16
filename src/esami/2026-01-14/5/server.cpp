#include "server.h"

#include <algorithm>

Server::Server(int id, int num_products)
    : id_(id), inventory_(num_products, 0) {}

void Server::initializeInventory(int product_id, int quantity) {
  if (product_id >= 0 && product_id < static_cast<int>(inventory_.size())) {
    inventory_[product_id] = quantity;
  }
}

int Server::processRequest(const Request& req) {
  if (req.product_id < 0 || req.product_id >= static_cast<int>(inventory_.size())) {
    return 0;
  }

  int available = inventory_[req.product_id];
  int provided = std::min(available, req.quantity);
  inventory_[req.product_id] -= provided;
  return provided;
}

void Server::receiveSupply(const Supply& supply) {
  if (supply.product_id >= 0 && supply.product_id < static_cast<int>(inventory_.size())) {
    inventory_[supply.product_id] += supply.quantity;
  }
}
