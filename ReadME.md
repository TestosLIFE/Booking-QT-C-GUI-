# Booking App - Qt C++

This is a desktop GUI application built in **C++ using Qt5**, simulating a hotel booking system. The project includes account management (registration/login), location selection, and full room reservation flow.

## 🔧 Technologies Used
- C++  
- Qt5 (QtWidgets)  
- Basic Object-Oriented Programming  
- File handling with plain text (`clients.txt`)

##  Features
- **Login / Register system** (data stored in `clients.txt`)
- **Postal code validation** (6-digit numeric check)
- **Destination selection** after login:
  - Mangalia
  - Navodari
- **Active destination: Saturn (Mangalia)** with 3 hotel options:
  - Cleopatra
  - Balada
  - Narcis
- **Full booking process**:
  - Date selection (with day/month/year and date validation)
  - Number of nights, rooms, beds, and email
  - Confirmation message after successful booking

##  Demo Sections
- The **"Venus"** option is marked as demo to avoid repetitive code (similar logic to Saturn)
- **"Navodari"** is also demo-only, for demonstration purposes

One full destination (Saturn) was implemented to show the complete logic and flow. Other destinations follow the same logic and can be easily extended with minimal effort.


##  How to Run
1. Open the project in Qt Creator or any IDE with Qt5 support
2. Make sure `clients.txt` is in the same folder (can be an empty file)
3. Compile and run the application

 Project Structure
- `booking123.cpp` – main application source code
- `clients.txt` – stores user credentials (plaintext)
- `README.md` – this file

---

  Project Purpose
This project was created to demonstrate:
- Hands-on GUI development in Qt and C++
- Logical flow design for booking/reservation systems
- Basic OOP and input validation
- File operations and user interaction

---

 This is a personal project for my **C++ Junior Developer portfolio**.  
 Entire logic was written manually without auto-generated code,
 Project made by Sandu Teodor-Robert
