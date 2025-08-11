# 📝 Console Notepad – C++ Linked List Editor with File Persistence

This is a simple **console-based notepad application** built in **C++**, using a **custom doubly linked list** for text storage and manipulation.  
It supports **arrow key navigation**, **real-time editing**, and **persistent saving to a file** so that your notes are never lost, even after closing the program.

---

## 📜 Project Overview
- **Language:** C++ (standard + `<conio.h>` for key handling)
- **Data Structure:** Doubly linked list with a **visual cursor node (`|`)**
- **Platform:** Windows console (uses `_getch()` for key events)
- **Key Features:**
  - Insert characters at the cursor position
  - Move the cursor left and right with arrow keys
  - Backspace to delete characters before the cursor
  - Press **Enter** for new lines
  - Automatic **file creation** if not found
  - Load previous text on start
  - **Auto-save after every edit**

---

## 🎯 Features
- **Linked List Text Storage:** Efficient insertion and deletion anywhere in the text.
- **Visual Cursor:** Keeps track of current editing position.
- **Keyboard Navigation:** Uses arrow keys for left/right movement.
- **File Handling:**
  - Loads existing file content into the editor.
  - Creates a new file if it doesn't exist.
  - Saves changes automatically after every edit.
- **Cross-line Editing:** Supports `Enter` for multi-line notes.

---

## 🛠 How It Works
- **`Node<T>` Class:** Represents each character and links to previous and next characters.
- **`Linkedlist<T>` Class:** Manages the head, tail, and cursor, along with insert, delete, and move operations.
- **File Persistence:**
  - On start: Reads file into linked list.
  - On every change: Writes linked list (excluding the cursor) to file.
- **Controls:**
  ----------------------------------------------------
  | Key             | Action                         |
  |-----------------|--------------------------------|
  | ⬅ Left Arrow   | Move cursor left               |
  | ➡ Right Arrow  | Move cursor right              |
  | ⌫ Backspace   | Delete character before cursor |
  | ⏎ Enter        | Insert new line                |
  | ESC            | Exit editor                     |
  ----------------------------------------------------

