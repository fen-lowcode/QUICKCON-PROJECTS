--@block

SELECT u.userID, u.firstname
FROM users u;

SELECT c.collectorID, c.firstname
from collectors c;

--@block

INSERT INTO users_to_collectors (
    userID,
    collectorID
)

values (
    2,
    1
)


--@block

SELECT u.firstname, c.firstname 
from users u
inner join users_to_collectors usc on
u.userID = usc.userID
inner join collectors c on 
c.collectorID = usc.collectorID