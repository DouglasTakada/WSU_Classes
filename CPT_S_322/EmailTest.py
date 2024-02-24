# Import smtplib for the actual sending function
import smtplib

# Import the email modules we'll need
from email.message import EmailMessage

import secrets, string

alphabet = string.digits
token = ''.join(secrets.choice(alphabet) for i in range(6))

print (token)

import smtplib, ssl

port = 587  # For starttls
smtp_server = "smtp.gmail.com"
sender_email = "ggerry003@gmail.com"
receiver_email = "griffin.gerry@wsu.edu"
password = input("Type your password and press enter:")
message = """\
Subject: Hi there

This message is sent from Python.""" + str(token)

context = ssl.create_default_context()
with smtplib.SMTP(smtp_server, port) as server:
    server.ehlo()  # Can be omitted
    server.starttls(context=context)
    server.ehlo()  # Can be omitted
    server.login(sender_email, password)
    server.sendmail(sender_email, receiver_email, message)