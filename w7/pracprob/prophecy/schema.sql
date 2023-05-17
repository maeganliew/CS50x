CREATE TABLE students_new (
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
    --PRIMARY KEY(student_name)
)

CREATE TABLE houses(
    id integer,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
    --PRIMARY KEY(house)
)

CREATE TABLE relationships(
    id INTEGER,
    student_name TEXT,
    house TEXT,
    PRIMARY KEY(id)
    --student_id INTEGER,
    --FOREIGN KEY (student_id) REFERENCES students(id),
    --FOREIGN KEY (student_name) REFERENCES students(students_name),
    --FOREIGN KEY (house) REFERENCES houses(house),
)