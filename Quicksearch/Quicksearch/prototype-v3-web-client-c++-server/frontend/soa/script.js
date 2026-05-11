

// Entry Point
window.onload = function() {
    const savedData = JSON.parse(localStorage.getItem('currentClient'));
    console.log(savedData);

    document.getElementById("top-client-name").value = savedData.CLIENTS_NAME;
    document.getElementById("top-client-address").value = savedData.ADDRESS;
    document.getElementById("top-client-contact").value = savedData.CONTACT_NO;
    document.getElementById("top-client-credentials").value = savedData.CREDENTIALS;
    document.getElementById("summary-mbps").value = savedData.PLAN;

    document.getElementById("stub-client-name").value = savedData.CLIENTS_NAME;
    document.getElementById("stub-client-address").value = savedData.ADDRESS;

    document.getElementById("stub2-client-name").value = savedData.CLIENTS_NAME;
    document.getElementById("stub2-client-address").value = savedData.ADDRESS;

    document.getElementById("stub-credentials").value = savedData.CREDENTIALS;
    document.getElementById("stub2-credentials").value = savedData.CREDENTIALS;
    

    console.log(savedData.CLIENTS_NAME);
    // Removes ONLY the 'currentClient' key
    localStorage.removeItem('currentClient');
};