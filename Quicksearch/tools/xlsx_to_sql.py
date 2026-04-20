import pandas as pd

# 1. Load the Excel (no headers)
df = pd.read_excel("Client_Masterlist.xlsx mitch.xlsx", sheet_name="AREA-F-AREA-E-AREA-H-FVR", header=None)

# 2. Alignment Fix: Capture exactly 20 columns (Index 0 to 19)
df = df.iloc[:, 0:20] 

# 3. Fill empty cells with 'N/A'
df = df.fillna("N/A")

table_name = "CUSTOMER_RECORDS"

# Define the columns in your table (excluding ID) to allow AUTO_INCREMENT to work
columns = (
    "CLIENTS_NAME, CREDENTIALS, ADDRESS, PLAN, DATE_APPLIED, CONTACT_NO, "
    "AGE, SEX, SOCIAL_MEDIA, OCCUPATION, DATE_OF_BIRTH, PLACE_OF_BIRTH, "
    "OPTICAL_INFO, SC_CONNECTOR, FIBER_DROP, TAPPING_CLIP, CABLE_TIE, "
    "F_CLAMP, REMARKS, INSTALLED_BY"
)

print(f"-- Generated MariaDB Insert Script for {len(df)} records\n")

for _, row in df.iterrows():
    # Clean up the row data and escape single quotes
    row_values = [str(val).strip().replace("'", "''") for val in row]

    # Skip the header row if "Clients Name" is in the first or second cell
    if "clients name" in row_values[0].lower() or "clients name" in row_values[1].lower():
        continue
    
    # Skip rows that are entirely "N/A" or empty
    if all(val == "N/A" or val == "" or val == "nan" for val in row_values):
        continue

    formatted_values = []
    for val in row_values:
        if val == "" or val.lower() == "nan" or val.lower() == "n/a":
            formatted_values.append("'N/A'") 
            
        else:
            formatted_values.append(f"'{val}'")

    # Join the values with commas
    sql_values = ", ".join(formatted_values)
    
    # Specify the columns in the INSERT statement
    print(f"INSERT INTO {table_name} ({columns}) VALUES ({sql_values});")
