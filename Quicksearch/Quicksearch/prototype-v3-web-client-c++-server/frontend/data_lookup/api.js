
async function fetchClientmasterList() {
    try {
        // // CRITICAL: You must await getToken() here
        // const tokenValue = await getToken();

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
    } catch (err) {
        console.error("Fetch failed: ", err);
        let countDisp = document.getElementById('rowCount');
        if (countDisp) countDisp.innerText = "Server Offline / Refused";
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
        status:    cells[1].innerText.trim(),
        id:        cells[2].innerText,
        name:      cells[3].innerText,
        creds:     cells[4].innerText,
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

        fetchClientmasterList();

    } catch(err) {
        console.error("Fetch failed: ", err);
    }
};



// get's the right token from document token
async function getToken() {
    return await localStorage.getItem('JWT');
}

