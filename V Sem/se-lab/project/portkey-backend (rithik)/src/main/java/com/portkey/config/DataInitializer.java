package com.portkey.config;

import com.portkey.entity.User;
import com.portkey.repository.UserRepository;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

@Component
public class DataInitializer implements CommandLineRunner {
    private final UserRepository userRepository;
    public DataInitializer(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @Override
    public void run(String... args) throws Exception {
        if(userRepository.findByEmail("admin@portkey.com").isEmpty()) {
            BCryptPasswordEncoder enc = new BCryptPasswordEncoder();
            User admin = User.builder()
                    .email("admin@portkey.com")
                    .name("Administrator")
                    .phone("0000000000")
                    .role("ROLE_ADMIN")
                    .passwordHash(enc.encode("admin123"))
                    .build();
            userRepository.save(admin);
            System.out.println("Created default admin: admin@portkey.com / admin123");
        }
    }
}
