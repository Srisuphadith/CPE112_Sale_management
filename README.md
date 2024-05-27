# CashierX By ShopWiz - Term Project - CPE 112 (Programming with Data structures)

## Project Overview

**Project Name: CashierX**

**Development Team : ShopWiz**

The Product Sales Management System is designed to streamline and manage the sales processes within a retail environment. This terminal-based application enables users to handle various aspects of sales, including product management, user management, and purchase tracking. By leveraging CSV files for data storage, the system ensures data persistence between sessions.

This README documents the term project for the CPE112 Programming with Data structures course in King Mongkut’s University of Technology Thonburi [(KMUTT)](https://www.kmutt.ac.th/).

## Table of Contents
1. [Project Overview](#project-overview)
2. [Education](#education)
3. [Development team](#development-team)
4. [Key Objectives](#key-objectives)
5. [Core Components](#core-components)
6. [System Workflow](#system-workflow)
7. [Benefits](#benefits)
8. [Features](#features)
9. [Functions](#functions)
10. [License](#license)

## Education
- King Mongkut’s University of Technology Thonburi [(KMUTT)](https://www.kmutt.ac.th/)
    - Bachelor of Engineering [(Website)](https://eng.kmutt.ac.th)
        - Computer Engineering [(CPE)](https://www.cpe.kmutt.ac.th)
            - CPE 112 - Programming with Data structures [(Syllabus)](https://drive.google.com/file/d/1q8DzZ1vEUM5RS1FiopvX1kUsBls0Rmtl/view)
                - Term Project

## Development team
Team name: TACTYCAM
| Full name             | ID            | Email                             | GitHub User |
| -                     | -             | -                                 | -           |
| Kanyaphat Chaithawip    | 66070501003   | <kanyaphat.chai@kmutt.ac.th>    |[@Kanyaphat10](https://github.com/Kanyaphat10)|
| Nuttawut Simcharoen    | 66070501019   | <Nuttawut.simc@kmutt.ac.th>    |[@Coconutkub](https://github.com/Coconutkub)|
| Ponprathan Kuearung        | 66070501036   | <ponprathan.kuea@kmutt.ac.th>        |[@pptCheer](https://github.com/pptCheer)|
| Srisuphadith Rattanaprasert        | 66070501052   | <srisuphadith.ratt@kmutt.ac.th>        |[@Srisuphadith](https://github.com/Srisuphadith)|
| Arkkhanirut Pandej     | 66070501062   | <arkkhanirut.pand@kmutt.ac.th>       |[@LuXeVi1](https://github.com/LuXeVi1)|
| Khunnapat Aubontara | 66070501068   | <khunnapat.aubo@kmutt.ac.th>      |[@Omgnatggboy](https://github.com/Omgnatggboy)|
| Yanakorn Tangprakhon      | 66070501071   | <yanakorn.tang@mail.kmutt.ac.th>       |[@FiFaKuBz](https://github.com/FiFaKuBz)|


## Key Objectives

- Efficient Product Management: Allow administrators to add, update, view, and delete products within the inventory.
- User Management: Enable registration and login functionality to differentiate between regular users and administrators.
- Sales Tracking: Maintain a history of user purchases and generate reports based on sales data.
- User-Friendly Interface: Provide an easy-to-navigate terminal interface for users to interact with the system.
- Data Persistence: Store all product, user, and sales data in CSV files, ensuring data is retained between program executions.

## Core Components

- Products: Managed by administrators, products have attributes such as ID, name, price, stock levels, and categories.
- Users: Both customers and administrators have user profiles, including login credentials and roles.
- Purchase History: Tracks the history of purchases made by users, including timestamps and product details.
- Cart: Allows users to add products to a virtual shopping cart and proceed to checkout.

## System Workflow

- Initialization: The system loads product, user, and purchase history data from CSV files upon startup.
- Authentication: Users can log in or register, with different functionalities available based on their roles (customer or admin).
- Product Management: Administrators can manage the product catalog, adding new products, updating existing ones, or removing products from the inventory.
- Shopping Experience: Customers can browse products, view product details, add items to their cart, and complete purchases through a checkout process.
- Order Processing: The system updates inventory levels, logs the purchase history, and generates reports on sales activities.
- Data Saving: Upon exiting, the system saves any changes made to the products, users, and purchase histories back to the respective CSV files.

## Benefits

- Scalability: The system's design allows for easy expansion and integration with more complex databases if needed in the future.
- Maintainability: Clear separation of concerns in the codebase ensures that individual components can be updated or replaced without affecting the overall system.
- User Roles: Differentiation between customer and admin roles provides secure and organized access to system functionalities.

## Features

- **Admin Functions:**
  - Manage products: Add, update, delete, view products.
  - View orders and generate sales reports.
  - View and manage user activity history.

- **Customer Functions:**
  - Register and log in.
  - View products and their details.
  - Add products to cart and checkout.
  - View and manage purchase history.

## Functions

### Utility Functions

- `clear_terminal()`: Clears the terminal screen.
- `load_data()`: Loads data from CSV files into linked lists.
- `remove_newline(char *str)`: Removes the newline character from a string.

### Node Creation Functions

- `struct Product *createNode_StrProduct(...)`
- `struct User *createNode_User(...)`
- `struct History *createNode_History(...)`
- `struct PurchaseHistory *createNode_PurchaseHistory(...)`
- `struct CartItem *createNode_CartItem(...)`

### Linked List Operations

- `void insertNode(struct Product **head, struct Product *newNode)`
- `void insertNodeUser(struct User **head, struct User *newNode)`

### Search Functions

- `struct User *searchUserByUsername(struct User *head, char Username[])`
- `struct User *searchUserByUsernameAndPassword(struct User *head, char *username, char *password)`
- `struct History *searchHistoryById(struct History *head, int id)`
- `struct History *searchHistoryByuser_id(struct History *head, int user_id)`
- `struct PurchaseHistory *searchPurchaseHistoryByUserID(struct PurchaseHistory *head, int UserID)`
- `struct PurchaseHistory *searchPurchaseHistoryByStockID(struct PurchaseHistory *head, char StockID[])`
- `struct CartItem *searchCartItemByKey(struct CartItem *head, int key)`
- `struct Product *searchProductByIDamdStockID(struct Product *head, char *ID, char *StockID)`

### User Interaction Functions

- `void login(struct ProductSales *ps)`
- `void register_user_NEW(struct ProductSales *ps)`
- `void register_user(struct ProductSales *ps)`
- `void main_menu(struct ProductSales *ps)`
- `void admin_menu(struct ProductSales *ps)`
- `void customer_menu(struct ProductSales *ps)`

### Product Management Functions

- `void manage_products(struct ProductSales *ps)`
- `void view_products(struct ProductSales *ps)`
- `void add_product(struct ProductSales *ps)`
- `void update_product(struct ProductSales *ps)`
- `void delete_product(struct ProductSales *ps)`
- `void view_all_products(struct ProductSales *ps)`

### Order and Cart Management Functions

- `void view_orders(struct ProductSales *ps)`
- `void add_to_cart(struct ProductSales *ps, char ID[6], char StockID[6], int amount)`
- `void view_cart(struct ProductSales *ps)`
- `void checkout(struct ProductSales *ps)`
- `void buy(struct ProductSales *ps, char ID[6], char StockID[6], int amount)`

### Reporting and Recommendation Functions

- `void generate_report(struct ProductSales *ps)`
- `void view_recommended_products(struct ProductSales *ps)`
- `void product_detail(struct ProductSales *ps)`
- `void search_by_cat(struct ProductSales *ps)`

### Compile & Exercute in 
Apple clang version 15.0.0 (clang-1500.3.9.4) | Target: arm64-apple-darwin23.5.0 | Thread model: posix