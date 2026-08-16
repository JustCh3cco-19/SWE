#ifndef EXAMPLES_ECOMMERCE_2026_01_14_EX3_SERVER_HPP_
#define EXAMPLES_ECOMMERCE_2026_01_14_EX3_SERVER_HPP_

#include <vector>

struct Request {
  int customer_id;
  int product_id;
  int quantity;
};

struct Supply {
  int product_id;
  int quantity;
};

// Stores inventory and processes requests for one server.
class Server {
  public:
  Server(int id, int num_products);

  void initializeInventory(int product_id, int quantity);

  // Processa richiesta customer, ritorna quantità effettivamente fornita
  int processRequest(const Request& req);

  // Riceve rifornimento dal fornitore
  void receiveSupply(const Supply& supply);

  int getId() const {
    return id_;
  }

  private:
  int id_;
  std::vector<int> inventory_;  // inventory_[i] = items disponibili per prodotto i
};

#endif
