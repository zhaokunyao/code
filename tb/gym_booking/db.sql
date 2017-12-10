
drop table classes;
create table classes (
    id int unsigned,
    class_name varchar(100),
    primary key (id)
);

insert into classes set id = 1, class_name = 'Boot Camp';
insert into classes set id = 2, class_name = 'Boxercise';
insert into classes set id = 3, class_name = 'Pilates';
insert into classes set id = 4, class_name = 'Yoga';
insert into classes set id = 5, class_name = 'Zumba';

drop table class_times;

create table class_times (
    id int unsigned,
    class_id int unsigned,
    time_name  varchar(100),
    capacity int unsigned,
    capacity_left int unsigned,
    primary key (id)
);
insert into class_times set id=1, class_id=1, time_name='Monday, 9:00', capacity=2, capacity_left=2;
insert into class_times set id=2, class_id=1, time_name='Tuesday, 9:00', capacity=2, capacity_left=2;
insert into class_times set id=3, class_id=1, time_name='Wednesday, 9:00', capacity=2, capacity_left=2;
insert into class_times set id=4, class_id=2, time_name='Thursday, 10:00', capacity=4, capacity_left=4;
insert into class_times set id=5, class_id=2, time_name='Friday, 10:00', capacity=4, capacity_left=4;
insert into class_times set id=6, class_id=3, time_name='Monday, 11:00', capacity=3, capacity_left=3;
insert into class_times set id=7, class_id=3, time_name='Wednesday, 11:00', capacity=3, capacity_left=3;
insert into class_times set id=8, class_id=3, time_name='Friday, 11:00', capacity=3, capacity_left=3;
insert into class_times set id=9, class_id=4, time_name='Tuesday, 13:00', capacity=2, capacity_left=2;
insert into class_times set id=10, class_id=4, time_name='Wednesday, 13:00', capacity=2, capacity_left=2;
insert into class_times set id=11, class_id=5, time_name='Friday, 14:00', capacity=2, capacity_left=2;

drop table booking_records;
create table booking_records (
    class_id int unsigned,
    time_id int unsigned,
    name varchar(100),
    mobile varchar(100)
);
