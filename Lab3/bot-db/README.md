# Instructions to run the project
## On Windows
You need to download python, pip and postgreqsl.

Here is tutorials how to do it:

For python3 and pip:

https://www.digitalocean.com/community/tutorials/how-to-install-python-3-and-set-up-a-local-programming-environment-on-windows-10
For postgresql:

http://www.postgresqltutorial.com/install-postgresql/

Then you have to run the bush script download-deps-windows.sh in project folder.

If it does not work try to run in terminal:

`pip install psycopg2-binary`

And then in line 11 in file db.py enter your postgresql superuser name, password and host if it is necessary:

```python
self.conn = psycopg2.connect(dbname='db', user= <name of your postgresql superuser> , host='localhost', password=<your password>, sslmode='require')
```
to create local postgres database.

## On Linux

Run the bush script using terminal in the project folder:
`chmod u+x download-deps-linux.sh`
