#include "customer.h"
#include "ecommercesystem.h"
#include <random>

Customer::Customer(int id, System& system, ECommerceSystem& ecommerce,
                   const Parameters& params, urng_t& rng)
    : TimerBasedEntity(system, 0.0, TimerMode::Once, params.T),
      id_(id),
      ecommerce_(ecommerce),
      params_(params),
      rng_(rng) {
  // Schedula il primo evento
  std::uniform_real_distribution<double> wait_dist(params_.A, params_.B);
  double initial_wait = wait_dist(rng);
  timer.resetWithDuration(initial_wait);
}

void Customer::update(TimerEnded) {
  // Sceglie server random
  std::uniform_int_distribution<int> server_dist(0, params_.S - 1);
  int server_id = server_dist(rng_);

  // Sceglie prodotto random
  std::uniform_int_distribution<int> product_dist(0, params_.P - 1);
  int product_id = product_dist(rng_);

  // Sceglie quantità random [1, Q]
  std::uniform_int_distribution<int> quantity_dist(1, params_.Q);
  int quantity = quantity_dist(rng_);

  ecommerce_.submitRequest(id_, server_id, product_id, quantity);

  // Schedula prossima azione
  scheduleNextAction(rng_);
}

void Customer::scheduleNextAction(urng_t& rng) {
  std::uniform_real_distribution<double> wait_dist(params_.A, params_.B);
  double wait_time = wait_dist(rng);
  timer.resetWithDuration(wait_time);
}
