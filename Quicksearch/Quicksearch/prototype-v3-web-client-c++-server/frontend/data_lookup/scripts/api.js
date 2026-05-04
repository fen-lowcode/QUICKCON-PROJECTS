


// get's the right token from document token
async function getToken() {
    return await localStorage.getItem('JWT');
}




async function fetchClientmasterList() {
    try {

        let response = await fetch('http://192.168.1.22:2222/get/customerlist', { 
            method: 'POST', 
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ 
                token:  await getToken()

            })
        });

        if (!response.ok) throw new Error("HTTP Error " + response.status);


        let dataArray = await response.json();
        renderTableRows(dataArray);

        let countDisp = document.getElementById('rowCount');
        if (countDisp) {
            countDisp.style.background = "lightblue";
            countDisp.style.color = "black";
        }
    } catch (err) {
        console.error("Fetch failed: ", err);
        let countDisp = document.getElementById('rowCount');
        if (countDisp) {
            countDisp.innerText = "Server Offline / Refused";
            countDisp.style.background = "darkred";
            countDisp.style.color = "white";
        }
    }
}



/* ============================================================
    4. EVENT HANDLING 
============================================================ */

async function deleteCustomer(e) {
    let row = e.target.closest('#tableBody tr');

    // Extracting data from table columns (Indices match <thead>)
    let cells = row.cells;
    let customerToDelete = {
        ID:                 cells[1].innerText,
        CLIENTS_NAME:       cells[2].innerText,
        CREDENTIALS:        cells[3].innerText,
    };

    console.log(customerToDelete);

    try {
        let res = await fetch("http://192.168.1.22:2222/delete/customerinfo", {
            method: "POST",
            headers: {
                "Content-Type" : "application/json"
            },
            body: JSON.stringify({
                token: await getToken(),
                customerToDel: customerToDelete
            })
        })
                    // Refreshes the list after deleting
        await fetchClientmasterList();
        filterTable();

    } catch(err) {
        console.error("Fetch failed: ", err);
    }
};

async function addCustomer(data) {

    try {
        const res = await fetch('http://192.168.1.22:2222/add/customer', {
            method: "POST",
            headers: {
                "Content-Type" : "application/json",
            },
            body: JSON.stringify({
                token: await getToken(),
                newCustomer: data
            })
        })

        await fetchClientmasterList();
    } catch(err) {
         console.error("Fetch failed: ", err);
    }
}


// PROFILE HANDLING for cuastomer info update

async function updateCustomer(data) {
    try {
        const res = await fetch('http://192.168.1.22:2222/update/customer', {
            method: "POST",
            headers: {
                "Content-Type" : "application/json",
            },
            body: JSON.stringify({
                token: await getToken(),
                updateCustomer: data
            })
        })
    } catch (err) {
         console.error("Fetch failed: ", err);
    }

    submitpaymentHistory(data);
}

async function submitpaymentHistory(data) {
     try {
        const res = await fetch('http://192.168.1.22:2222/add/customer/history', {
            method: "POST",
            headers: {
                "Content-Type" : "application/json",
            },
            body: JSON.stringify({
                token: await getToken(),
                paymentHistory: data
            })
        })
    } catch (err) {
         console.error("Fetch failed: ", err);
    }
}

async function getPaymentHistory(id) {
    try {
        const token = await getToken();
        
        const res = await fetch('http://192.168.1.22:2222/get/customer/history', {
            method: "POST",
            headers: {
                "Content-Type" : "application/json",
            },
            body: JSON.stringify({
                token: token,
                id: id // Sending 'id' here
            })
        });

        if (!res.ok) {
            const errorText = await res.text();
            throw new Error(`Server returned ${res.status}: ${errorText}`);
        }

        const historyArray = await res.json();
        
        // Ensure we pass the actual data received to the renderer
        renderHistoryRows(historyArray);

    } catch (err) {
         console.error("Fetch failed: ", err.message);
         document.getElementById('payment-history-list').innerHTML = 
            `<tr><td colspan="5" style="color:red; text-align:center;">Failed to load history: ${err.message}</td></tr>`;
    }
}