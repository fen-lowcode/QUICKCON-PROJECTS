
async function fetchClientmasterList() {
    try {

        let response = await fetch('http://127.0.0.1:2222/get/customerlist', { 
            method: 'POST', 
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ 
                token:  await getToken()

            })
        });

        if (!response.ok) throw new Error("HTTP Error " + response.status);

        console.log(document.cookie)

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
    4. EVENT HANDLING (The Bridge)
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
        let res = await fetch("http://127.0.0.1:2222/delete/customerinfo", {
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
    const res = await fetch('http://127.0.0.1:2222/add/customer', {
        method: "POST",
        headers: {
            "Content-Type" : "application/json",
        },
        body: JSON.stringify({
            token: await getToken(),
            newCustomer: data
        })
    })
}



// get's the right token from document token
async function getToken() {
    return await localStorage.getItem('JWT');
}

