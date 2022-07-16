import cgi, cgitb
cgitb.enable()

input_data = cgi.FieldStorage()

print('<h1>Addition Results</h1>')
try:
    num1 = int(input_data["num1"].value)
    num2 = int(input_data["num2"].value)
except:
    print('<output>Sorry, the script cannot turn your inputs into numbers (integers).</output>')
    raise SystemExit(1)
print('<output>{0} + {1} = {2}</output>'.format(num1, num2, num1 + num2))
