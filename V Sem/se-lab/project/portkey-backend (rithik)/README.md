# portkey-backend

This is a simplified Spring Boot (Maven) backend skeleton for the PORTKEY Food Delivery project.

## Features included:
- JWT auth (register/login)
- Role-based access (ROLE_ADMIN default created)
- Restaurants, Orders, Payments (basic endpoints)
- H2 in-memory profile for quick testing
- MySQL profile configured (edit credentials in application-mysql.properties)

## Run (H2 in-memory)
- Ensure Java 17+ is installed
- Build: mvn clean package
- Run: java -jar target/portkey-backend-1.0.0.jar

## Default credentials (created at startup):
- admin@portkey.com / admin123

## Notes
This is a starter skeleton focused on Rithik's backend responsibilities. Extend services, add DTOs, validations, tests and more advanced features as needed.
