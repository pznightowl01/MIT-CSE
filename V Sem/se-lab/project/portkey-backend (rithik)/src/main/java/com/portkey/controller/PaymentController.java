package com.portkey.controller;

import com.portkey.entity.Order;
import com.portkey.entity.Payment;
import com.portkey.repository.OrderRepository;
import com.portkey.repository.PaymentRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/payments")
public class PaymentController {
    private final PaymentRepository paymentRepo;
    private final OrderRepository orderRepo;

    public PaymentController(PaymentRepository paymentRepo, OrderRepository orderRepo) {
        this.paymentRepo = paymentRepo;
        this.orderRepo = orderRepo;
    }

    @PostMapping("/process")
    public ResponseEntity<?> process(@RequestBody Map<String, Object> payload) {
        try {
            Long orderId = Long.valueOf(payload.get("orderId").toString());
            String method = payload.get("method").toString();
            Order order = orderRepo.findById(orderId).orElseThrow(() -> new RuntimeException("Order not found"));
            Payment p = paymentRepo.findAll().stream().filter(x->x.getOrderId().equals(orderId)).findFirst().orElse(null);
            if(p==null) {
                p = Payment.builder()
                        .orderId(orderId)
                        .amount(order.getTotalAmount())
                        .method(method)
                        .status("PENDING")
                        .transactionRef(java.util.UUID.randomUUID().toString())
                        .build();
                paymentRepo.save(p);
            }
            p.setStatus("SUCCESS");
            paymentRepo.save(p);
            order.setStatus("PREPARING");
            orderRepo.save(order);
            return ResponseEntity.ok(p);
        } catch(Exception ex) {
            ex.printStackTrace();
            return ResponseEntity.badRequest().body(ex.getMessage());
        }
    }
}
