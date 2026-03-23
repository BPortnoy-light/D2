CREATE TABLE MarketWeek (
    week_id INTEGER PRIMARY KEY,
    date TEXT NOT NULL
);

CREATE TABLE MarketStall (
    stall_id INTEGER PRIMARY KEY,
    week_id INTEGER,
    category TEXT,         -- food / artisan
    price INTEGER,
    booked BOOLEAN,
    FOREIGN KEY (week_id) REFERENCES MarketWeek(week_id)
);

CREATE TABLE Waitlist (
    waitlist_id INTEGER PRIMARY KEY,
    week_id INTEGER,
    category TEXT,
    FOREIGN KEY (week_id) REFERENCES MarketWeek(week_id)
);

CREATE TABLE WaitlistEntry (
    entry_id INTEGER PRIMARY KEY,
    waitlist_id INTEGER,
    vendor_id INTEGER,
    position INTEGER,
    FOREIGN KEY (waitlist_id) REFERENCES Waitlist(waitlist_id),
    FOREIGN KEY (vendor_id) REFERENCES Vendor(vendor_id)
);

CREATE TABLE Vendor (
    vendor_id INTEGER PRIMARY KEY,
    business_name TEXT,
    owner_name TEXT,
    email TEXT,
    phone TEXT,
    mailing TEXT,
    category TEXT,
    compliance_ok BOOLEAN
);

CREATE TABLE BookingRequest (
    request_id INTEGER PRIMARY KEY,
    vendor_id INTEGER,
    stall_id INTEGER,
    week_id INTEGER,
    status TEXT,   -- pending / approved / rejected

    FOREIGN KEY (vendor_id) REFERENCES Vendor(vendor_id),
    FOREIGN KEY (stall_id) REFERENCES MarketStall(stall_id),
    FOREIGN KEY (week_id) REFERENCES MarketWeek(week_id)
);

CREATE TABLE ViewRequest (
    view_id INTEGER PRIMARY KEY,
    vendor_id INTEGER,
    request_type TEXT,   -- "dashboard", "schedule"

    FOREIGN KEY (vendor_id) REFERENCES Vendor(vendor_id)
);

CREATE TABLE StorageRequest (
    storage_id INTEGER PRIMARY KEY,
    action TEXT,   -- "insert", "update", "delete"
    entity TEXT    -- "stall", "waitlist", etc.
);

CREATE TABLE Notification (
    notification_id INTEGER PRIMARY KEY,
    vendor_id INTEGER,
    message TEXT,
    date TEXT,

    FOREIGN KEY (vendor_id) REFERENCES Vendor(vendor_id)
);