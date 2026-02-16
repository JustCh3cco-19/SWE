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

  int processRequest(const Request& req);
  void receiveSupply(const Supply& supply);

  int getId() const { return id_; }

 private:
  int id_;
  std::vector<int> inventory_;
};

#endif
