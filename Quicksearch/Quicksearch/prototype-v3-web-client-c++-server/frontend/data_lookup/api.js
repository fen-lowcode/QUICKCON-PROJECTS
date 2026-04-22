
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
async function deleteRow(e) {
    let row = e.target.closest('#tableBody tr');

    // Extracting data from table columns (Indices match <thead>)
    let cells = row.cells;
    let customerToDelete = {
        status:    cells[1].innerText.trim(),
        id:        cells[2].innerText,
        name:      cells[3].innerText,
        creds:     cells[4].innerText,
        address:   cells[5].innerText,
        plan:      cells[6].innerText,
        applied:   cells[7].innerText,
        contact:   cells[8].innerText,
        age:       cells[9].innerText,
        sex:       cells[10].innerText,
        social:    cells[11].innerText,
        job:       cells[12].innerText,
        dob:       cells[13].innerText,
        pob:       cells[14].innerText,
        optical:   cells[15].innerText,
        sc:        cells[16].innerText,
        fiber:     cells[17].innerText,
        clip:      cells[18].innerText,
        tie:       cells[19].innerText,
        fclamp:    cells[20].innerText,
        remarks:   cells[21].innerText,
        tech:      cells[22].innerText
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

    } catch(err) {
        console.error("Fetch failed: ", err);
    }
};



// get's the right token from document token
async function getToken() {
    return await localStorage.getItem('JWT');
}

