package com.portkey.entity;

import jakarta.persistence.*;
import lombok.*;

import java.time.LocalDateTime;
import java.util.List;

@Entity
@Table(name = "orders")
@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class Order {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long customerId;
    private Long restaurantId;

    private Double totalAmount;

    private String status; // PLACED, PREPARING, DISPATCHED, DELIVERED, CANCELLED

    private LocalDateTime createdAt;
}
