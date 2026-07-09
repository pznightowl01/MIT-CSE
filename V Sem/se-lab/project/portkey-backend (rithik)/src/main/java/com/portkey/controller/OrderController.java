package com.portkey.controller;

import com.portkey.entity.Order;
import com.portkey.entity.Payment;
import com.portkey.repository.OrderRepository;
import com.portkey.repository.PaymentRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.*;

@RestController
@RequestMapping("/api/orders")
public class OrderController {
    private final OrderRepository orderRepo;
    private final PaymentRepository paymentRepo;

    public OrderController(OrderRepository orderRepo, PaymentRepository paymentRepo) {
        this.orderRepo = orderRepo;
        this.paymentRepo = paymentRepo;
    }

    @PostMapping("/place")
    public ResponseEntity<?> placeOrder(@RequestBody Map<String,Object> payload) {
        try {
            Long customerId = Long.valueOf(payload.get("customerId").toString());
            Long restaurantId = Long.valueOf(payload.get("restaurantId").toString());
            Double total = Double.valueOf(payload.get("totalAmount").toString());
            String paymentMethod = payload.getOrDefault("paymentMethod","COD").toString();

            Order o = Order.builder()
                    .customerId(customerId)
                    .restaurantId(restaurantId)
                    .totalAmount(total)
                    .status("PLACED")
                    .createdAt(LocalDateTime.now())
                    .build();
            Order saved = orderRepo.save(o);

            Payment p = Payment.builder()
                    .orderId(saved.getId())
                    .amount(saved.getTotalAmount())
                    .method(paymentMethod)
                    .status(paymentMethod.equalsIgnoreCase("COD")?"SUCCESS":"PENDING")
                    .transactionRef(UUID.randomUUID().toString())
                    .build();
            paymentRepo.save(p);

            if(paymentMethod.equalsIgnoreCase("COD")) {
                saved.setStatus("DISPATCHED");
                orderRepo.save(saved);
            }
            return ResponseEntity.ok(Map.of("order", saved, "payment", p));
        } catch(Exception ex) {
            ex.printStackTrace();
            return ResponseEntity.badRequest().body(ex.getMessage());
        }
    }

    @GetMapping("/{id}")
    public ResponseEntity<?> get(@PathVariable Long id) {
        return orderRepo.findById(id).map(ResponseEntity::ok).orElse(ResponseEntity.notFound().build());
    }
}
