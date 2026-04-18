async function fetchClientmasterList() {
    try {
        let response = await fetch('http://127.0.0.1:2222/getData', { 
            method: 'POST', 
            body: JSON.stringify({ 
                token: "token"
            })
        });
        if (response.ok === false) throw new Error("HTTP Error " + response.status);

        let dataArray = await response.json();
        renderTableRows(dataArray);
    } catch (err) {
        console.error("Fetch failed: ", err);
        let countDisp = document.getElementById('rowCount');
        if (countDisp) countDisp.innerText = "Offline / Connection Error";
    }
}

