# Small Business Management System (SBMS)

## Introduction

The Small Business Management System (SBMS) is a comprehensive, command-line tool designed to help small businesses efficiently manage their operations. This robust system provides an all-in-one solution for inventory, orders, customers, and finances management.

## Features

- Inventory Management: Add, update, delete, and view items
- Order Management: Place orders, update status, view history
- Customer Management: Manage customer information
- Financial Management: Generate sales, profit, and inventory reports
- User Management: Create and manage user accounts
- Data Backup and Restore: Ensure data safety

## Why Choose SBMS?

In today's fast-paced business environment, small business owners need a reliable, efficient, and cost-effective way to manage their operations. That's where SBMS comes in. Our system combines multiple business management functions into a single, easy-to-use application, eliminating the need for multiple software solutions and reducing overhead costs.

We understand that data security is paramount. That's why SBMS comes with built-in user authentication and data backup features, ensuring your business information remains secure. But we don't stop at security - SBMS is designed to grow with your business.

What sets SBMS apart is its comprehensive reporting capabilities. Make informed decisions with detailed financial and inventory reports, giving you a clear picture of your business's health at any given moment. By choosing SBMS you're gaining a powerful tool that will help drive your business forward.


[YouTube Demo Video](https://youtu.be/TwM4x0S1GDw)
For more details about the project, refer to the  [About Section](./ABOUT.md).

## Installation

### Prerequisites

**GCC Compiler:**
- Linux: Pre-installed or via `sudo apt install gcc`.
- Windows: [MinGW](https://sourceforge.net/projects/mingw-w64/).
- macOS: Install via [Homebrew](https://brew.sh/) with `brew install gcc`.

**Make Utility:**
- Linux: Included in `build-essential` on Debian/Ubuntu.
- Windows: [MSYS2](https://www.msys2.org/).
- macOS: Install with `brew install make`.

### Build and Install

1. Clone the repository:
   ```bash
   git clone https://github.com/chiemezie1/SmallBusinessManagementSystem.git
   cd SmallBusinessManagementSystem
   ```
2. Compile the project:
   ```bash
   make
   ```
3. Run the application:
   ```bash
   ./bin/sbms
   ```

## Usage

Log in using the default admin credentials:
- Username: `admin`
- Password: `0000`

2. After logging in, you'll see the main menu with various options:

   - Admin (only visible to admin users)
   - Inventory Management
   - Order Management
   - Customer Management
   - Financial Management
   - Change Password
   - Logout

3. Navigate through the menus using the number keys and follow the on-screen prompts to perform various actions.

## Admin Functions

As an admin user, you have access to additional functions:

1. Create new user accounts
2. Display a list of all users
3. Update passwords for any user
4. Create a backup
5. Restore system data from a previous backup

### Inventory and Order Management

- Add, update, delete, or view items.
- Place orders, update their status, and view history.

### Financial and Customer Management

- Generate sales and profit reports.
- Manage customer information.

## Data Backup and Restore

Regular backups ensure data safety. Use the admin menu to create or restore backups as needed.

## Customization

SBMS is designed to be easily customizable. You can modify the source code to add new features or adjust existing ones to better fit your business needs.

## Contributing

Contributions are welcome! Fork the repository, create a feature branch, commit changes, and submit a pull request.

## License
See License. 