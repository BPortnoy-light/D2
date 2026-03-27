-- Enable foreign key support 
PRAGMA foreign_keys = ON;


-- USER TABLE
-- Stores all system users

CREATE TABLE IF NOT EXISTS User 
(
    Username TEXT PRIMARY KEY,         -- unique login identifier
    Permission TEXT NOT NULL           -- Vendor / Operator / Admin
);


-- VENDOR TABLE
-- Extra info only for vendors

CREATE TABLE IF NOT EXISTS Vendor 
(
    Username TEXT PRIMARY KEY,         -- links to User
    Category TEXT NOT NULL,            -- Food or Artisan
    BusinessName TEXT NOT NULL,
    OwnerName TEXT NOT NULL,
    Email TEXT NOT NULL,
    Phone TEXT NOT NULL,
    Mailing TEXT NOT NULL,
    FOREIGN KEY (Username) REFERENCES User(Username)
        ON DELETE CASCADE ON UPDATE CASCADE
);


-- MARKET ORGANIZER

CREATE TABLE IF NOT EXISTS MarketOrganizer 
(
    Username TEXT PRIMARY KEY,
    FOREIGN KEY (Username) REFERENCES User(Username)
        ON DELETE CASCADE ON UPDATE CASCADE
);


-- SYSTEM ADMIN

CREATE TABLE IF NOT EXISTS SystemAdministrator 
(
    Username TEXT PRIMARY KEY,
    FOREIGN KEY (Username) REFERENCES User(Username)
        ON DELETE CASCADE ON UPDATE CASCADE
);


-- MARKET SCHEDULE
-- Stores 4 weeks of markets

CREATE TABLE IF NOT EXISTS MarketSchedule 
(
    WeekID INTEGER PRIMARY KEY,
    MarketDate TEXT NOT NULL,
    FoodCapacity INTEGER NOT NULL DEFAULT 2,
    ArtisanCapacity INTEGER NOT NULL DEFAULT 2
);


-- BOOKING REQUEST
-- Created whenever vendor requests booking

CREATE TABLE IF NOT EXISTS BookingRequest 
(
    RequestID INTEGER PRIMARY KEY AUTOINCREMENT,
    Username TEXT NOT NULL,
    WeekID INTEGER NOT NULL,
    Category TEXT NOT NULL,
    Status TEXT NOT NULL,              -- Pending / Approved / Waitlisted / Removed
    RequestTime TEXT NOT NULL,
    FOREIGN KEY (Username) REFERENCES Vendor(Username),
    FOREIGN KEY (WeekID) REFERENCES MarketSchedule(WeekID)
);


-- BOOKING 
-- Stores actual stall bookings

CREATE TABLE IF NOT EXISTS Booking 
(
    BookingID INTEGER PRIMARY KEY AUTOINCREMENT,
    Username TEXT NOT NULL,
    WeekID INTEGER NOT NULL,
    Category TEXT NOT NULL,
    Status TEXT NOT NULL,              -- Booked / Cancelled
    FOREIGN KEY (Username) REFERENCES Vendor(Username),
    FOREIGN KEY (WeekID) REFERENCES MarketSchedule(WeekID)
);


-- COMPLIANCE DOCUMENTS
-- Each vendor must have documents

CREATE TABLE IF NOT EXISTS ComplianceDocumentation 
(
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    Username TEXT NOT NULL,
    Type TEXT NOT NULL,                -- BusinessLicence / Insurance / OFHC
    ExpirationDate TEXT NOT NULL,
    ProviderName TEXT NOT NULL,
    Status INTEGER NOT NULL,           -- 1 = valid, 0 = expired
    FOREIGN KEY (Username) REFERENCES Vendor(Username)
);

-- WAITLIST
-- FIFO queue per (Week + Category)

CREATE TABLE IF NOT EXISTS Waitlist 
(
    WeekID INTEGER NOT NULL,
    Category TEXT NOT NULL,
    RequestID INTEGER NOT NULL,
    Position INTEGER NOT NULL,         -- FIFO order (1 = first)
    PRIMARY KEY (WeekID, Category, Position),
    FOREIGN KEY (RequestID) REFERENCES BookingRequest(RequestID)
);