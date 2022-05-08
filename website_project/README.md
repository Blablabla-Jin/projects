# Toolman
Boming Jin(Also another parterner)

All .js files are in javascript folder.
All media files are in images folder.
We used Animate.css as library.
All useful .php backend files are in php folder.

Established both frontend and backend.(Used AWS as the server, but stopped the server since it's not for free)

This website is a website which is trying to offer services like Yelp.

Users could sign in for accounts.

Only users who logged in could able to submit reviews and refresh the part of the page(not the whole page by using AJAX and jQuery)

We used PHP Data Object(PDO) API for database access.

Each input/textarea place is validated in the backend and frontend

We used S3 bucket to store the image(s) that users uploaded, but now is not working since we closed our AWS things.

Instructions:

We prepopulated 5 restraurants in the databse for searching, whcih are "soyummy, Coco milktea, The Ship, The Alley, August 8". Users should input exact name or rate of restaurants for searching restaurants properly. If want to search based on rate, then do not enter anything into input box. One/Multiple restaurants will all showed on the left side of the page(include one image if they uploaded for that restaurant), and markers will showed up on the map. On the top right corner when use logged in the icon will trun into "Log Out", and if not logged in, the icon is showing "Log In" and lead to the log in page.

For individual object page reviews, coords, marker will showed properly, users could submit the review on the same page at the end of the leftside. Success messages or fail messages will showed after submission. Used ajax to render the page partially.

On the submission page, only logged in user could sbumit new object, user could submit image to the S3 bucket. Right click will choose the coordinate on the map directly(the coords will auto filled in the proper input). The button is in the bottom left corner.

For registration page, usre could sign up or log in in the different page, and message will show if the action is success or fail.