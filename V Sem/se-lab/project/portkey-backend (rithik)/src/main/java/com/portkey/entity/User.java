package com.portkey.entity;

import jakarta.persistence.*;
import lombok.*;

@Entity
@Table(name = "users")
@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class User {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(unique = true, nullable = false)
    private String email;

    @Column(nullable = false)
    private String passwordHash;

    private String name;
    private String phone;

    @Column(nullable = false)
    private String role; // ROLE_CUSTOMER, ROLE_RESTAURANT, ROLE_ADMIN, ROLE_DELIVERY
}
