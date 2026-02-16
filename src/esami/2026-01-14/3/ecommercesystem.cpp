#include "ecommercesystem.h"
#include <random>

ECommerceSystem::ECommerceSystem(System& system, const Parameters& params, urng_t& rng)
    : params_(params), current_time_(0.0), missed_sales_(0) {
  
  system.addObserver(this);
  
  servers_.reserve(params.S);
  for (int i = 0; i < params.S; ++i) {
    servers_.emplace_back(i, params.P);
  }

  // Inizializza inventory random [0, Q] per ogni prodotto in ogni server
  std::uniform_int_distribution<int> init_dist(0, params.Q);
  for (auto& server : servers_) {
    for (int p = 0; p < params.P; ++p) {
      server.initializeInventory(p, init_dist(rng));
    }
  }
}

void ECommerceSystem::submitRequest(int customer_id, int server_id,
                                    int product_id, int quantity) {
  if (server_id < 0 || server_id >= params_.S) {
    return;
  }

  // Crea richiesta pendente che verrà processata dopo tempo A
  PendingRequest req{customer_id, server_id, product_id, quantity, current_time_ + params_.A};
  pending_requests_.push(req);
}

void ECommerceSystem::update() {
  current_time_ += params_.T;
  
  // Processa tutte le richieste il cui tempo è arrivato
  while (!pending_requests_.empty() && pending_requests_.top().process_time <= current_time_) {
    const PendingRequest& req = pending_requests_.top();
    
    if (req.server_id >= 0 && req.server_id < params_.S) {
      Request server_req{req.customer_id, req.product_id, req.quantity};
      int provided = servers_[req.server_id].processRequest(server_req);
      
      if (provided < req.quantity) {
        missed_sales_++;
      }
    }
    
    pending_requests_.pop();
  }
}

void ECommerceSystem::submitSupply(int supplier_id, int server_id,
                                   int product_id, int quantity) {
  (void)supplier_id;  // Evita warning unused
  if (server_id < 0 || server_id >= params_.S) {
    return;
  }

  Supply supply{product_id, quantity};
  servers_[server_id].receiveSupply(supply);
}
