SELECT
    u.name,
    u.phone,
    SUM(o.subtotal) usersum,
    AVG(o.subtotal) useravg,
    MAX(o.created) lastorder
FROM
    users u
LEFT JOIN orders o ON
    o.user_id = u.id
GROUP BY
    u.name,
    u.phone;