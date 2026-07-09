package com.portkey.controller;

import com.portkey.config.JwtTokenUtil;
import com.portkey.dto.AuthRequest;
import com.portkey.dto.AuthResponse;
import com.portkey.dto.RegisterRequest;
import com.portkey.entity.User;
import com.portkey.service.UserService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.Optional;

@RestController
@RequestMapping("/api/auth")
public class AuthController {
    private final UserService userService;
    private final JwtTokenUtil jwtTokenUtil;

    public AuthController(UserService userService, JwtTokenUtil jwtTokenUtil) {
        this.userService = userService;
        this.jwtTokenUtil = jwtTokenUtil;
    }

    @PostMapping("/register")
    public ResponseEntity<?> register(@RequestBody RegisterRequest req) {
        if (userService.findByEmail(req.getEmail()).isPresent()) {
            return ResponseEntity.badRequest().body("Email already in use");
        }
        User u = User.builder()
                .email(req.getEmail())
                .name(req.getName())
                .phone(req.getPhone())
                .role(req.getRole() == null ? "ROLE_CUSTOMER" : req.getRole())
                .build();
        userService.register(u, req.getPassword());
        return ResponseEntity.ok("User registered");
    }

    @PostMapping("/login")
    public ResponseEntity<?> login(@RequestBody AuthRequest req) {
        Optional<User> opt = userService.findByEmail(req.getEmail());
        if (opt.isEmpty()) return ResponseEntity.status(401).body("Invalid credentials");
        User u = opt.get();
        if (!userService.verifyPassword(req.getPassword(), u.getPasswordHash())) {
            return ResponseEntity.status(401).body("Invalid credentials");
        }
        String token = jwtTokenUtil.generateToken(u.getEmail(), u.getRole());
        return ResponseEntity.ok(new AuthResponse(token));
    }
}
