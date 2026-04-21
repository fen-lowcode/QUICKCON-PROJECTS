
async function fetchClientmasterList() {
    try {
        // // CRITICAL: You must await getToken() here
        // const tokenValue = await getToken();

        let response = await fetch('http://192.168.1.21:2222/getData', { 
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

// get's the right token from document token
async function getToken() {
    return await localStorage.getItem('JWT');
}
