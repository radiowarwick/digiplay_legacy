:%s/"id" INTEGER not null/"id" SERIAL/g
:%s/VARCHAR(10)/VARCHAR/g
:15
i
create database digiplay;
create user digiplay_user;
\c digiplay
begin transaction;


��5Gi��=
end transaction;

:wq
