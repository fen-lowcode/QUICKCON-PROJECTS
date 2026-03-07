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

    select * from collectors;