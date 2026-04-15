// 1. Modified generateRows to accept real data from the database
function generateRows(dataList) {
    const tableBody = document.getElementById('tableBody');
    let html = "";

    // dataList is now the array of objects returned from your C++ backend
    dataList.forEach((customer, index) => {
        // Map your C++ JSON keys to the table columns
        const status = customer.status || "ACTIVE"; // Default if status isn't in DB yet
        
        html += `
            <tr>
                <td><span class="status-badge ${status.toLowerCase()}">${status}</span></td>
                <td>${customer.id}</td>
                <td>${customer.name}</td>
                <td>${customer.credentials || 'N/A'}</td>
                <td>${customer.address}</td>
                <td>${customer.plan}</td>
                <td>${customer.date_applied}</td>
                <td>${customer.contact_no}</td>
                <td>${customer.age}</td>
                <td>${customer.sex}</td>
                <td>${customer.social_media}</td>
                <td>${customer.occupation}</td>
                <td>${customer.dob}</td>
                <td>${customer.pob}</td>
                <td>${customer.optical_info}</td>
                <td>${customer.sc_connector}</td>
                <td>${customer.fiber_drop}</td>
                <td>${customer.tapping_clip}</td>
                <td>${customer.cable_tie}</td>
                <td>${customer.f_clamp}</td>
                <td>${customer.remarks}</td>
                <td>${customer.installed_by}</td>
            </tr>
        `;
    });

    tableBody.innerHTML = html;
    document.getElementById('rowCount').innerText = `${dataList.length} Records Loaded`;
}

// 2. Updated Event Listener to bridge the Fetch with the UI
window.addEventListener('load', async () => {
    try {
        const res = await fetch('http://127.0.0.1:2222/getData', {
            method: 'POST',
        });

        if (!res.ok) throw new Error("Server responded with error");

        const data = await res.json(); 
        console.log("Received Data:", data);
        
        // Pass the REAL data to the generator
        generateRows(data);
        
    } catch (error) {
        console.warn("Failed to fetch customer data:", error);
        // Fallback or error message in UI
        document.getElementById('rowCount').innerText = "Error loading records";
    }
});

function filterTable() {
    let input = document.getElementById("tableSearch");
    let filter = input.value.toUpperCase();
    let tr = document.getElementById("tableBody").getElementsByTagName("tr");

    for (let i = 0; i < tr.length; i++) {
        tr[i].style.display = (tr[i].textContent || tr[i].innerText).toUpperCase().indexOf(filter) > -1 ? "" : "none";
    }
}

// This is the professional way to do it
window.addEventListener('load', () => {
    console.log("Hello");
});

window.addEventListener('load', () => {
    generateRows(2000);
});

