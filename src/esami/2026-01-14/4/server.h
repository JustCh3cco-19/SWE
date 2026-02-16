#ifndef SERVER_H
#define SERVER_H

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

class Server {
 public:
  Server(int id, int num_products);

  void initializeInventory(int product_id, int quantity);
  
  // Processa richiesta customer, ritorna quantità effettivamente fornita
  int processRequest(const Request& req);
  
  // Riceve rifornimento dal fornitore
  void receiveSupply(const Supply& supply);

  int getId() const { return id_; }

 private:
  int id_;
  std::vector<int> inventory_;  // inventory_[i] = items disponibili per prodotto i
};

#endif
