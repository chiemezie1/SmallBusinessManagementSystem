# Small Business Management System (SBMS)

## Project Overview

The Small Business Management System (SBMS) is a comprehensive, command-line application designed to help small businesses efficiently manage their operations. This robust system provides an all-in-one solution for inventory management, order processing, customer relationship management, and financial reporting.

## Key Features

1. User Authentication and Authorization
2. Inventory Management
3. Order Management
4. Customer Management
5. Financial Reporting
6. Data Backup and Restore

## File Structure and Descriptions

### Source Files (src/)

1. `admin.c`: Handles administrative functions such as user management, data backup, and restoration.
2. `customers.c`: Manages customer-related operations like adding, updating, and deleting customer records.
3. `financial.c`: Generates financial reports including sales reports, profit reports, and inventory value reports.
4. `inventory.c`: Manages inventory-related operations such as adding, updating, and deleting inventory items.
5. `main.c`: Contains the main program loop and user interface for the application.
6. `orders.c`: Handles order-related operations including placing orders and updating order statuses.
7. `utils.c`: Provides utility functions used across the application, such as input validation and date parsing.

### Header Files (include/)

1. `admin.h`: Declarations for administrative functions and structures.
2. `common.h`: Common definitions and structures used across the application.
3. `customers.h`: Declarations for customer-related functions and structures.
4. `financial.h`: Declarations for financial reporting functions and structures.
5. `inventory.h`: Declarations for inventory-related functions and structures.
6. `orders.h`: Declarations for order-related functions and structures.
7. `utils.h`: Declarations for utility functions.

### Test Files (test/)

1. `test_customers.c`: Unit tests for customer-related functions.
2. `test_financial.c`: Unit tests for financial reporting functions.
3. `test_inventory.c`: Unit tests for inventory-related functions.
4. `test_orders.c`: Unit tests for order-related functions.
5. `unity.c`: Unity testing framework implementation.
6. `unity.h`: Unity testing framework header.

### Other Files

1. `Makefile`: Defines compilation and build rules for the project.
2. `LICENSE`: Contains the MIT License text for the project.
3. `AUTHOR`: Information about the project author.
4. `README.md`: Provides an overview of the project, installation instructions, and usage guidelines.

## Building and Running the Project

To build the project, ensure you have GCC and Make installed on your system. Then, follow these steps:

1. Clone the repository
2. Navigate to the project directory
3. Run `make` to compile the project
4. Execute the compiled binary: `./bin/sbms`

## Testing

To run the unit tests, use the following command:

