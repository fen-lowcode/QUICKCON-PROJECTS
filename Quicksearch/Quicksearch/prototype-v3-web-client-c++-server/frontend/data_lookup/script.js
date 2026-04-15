const firstNames = ["Juan", "Maria", "Ricardo", "Elena", "Antonio", "Sonia", "Paolo", "Joshua", "Mateo", "Liza", "Stephen", "Renaldo", "Rose"];
const lastNames = ["Dela Cruz", "Santos", "Reyes", "Garcia", "Bautista", "Mendoza", "Pascual", "Aquino", "Villanueva", "Lim", "Blanco", "Bocol"];
const locations = ["Quezon City", "Makati", "Caloocan", "Pasig", "Taguig", "Manila", "Davao", "Cebu"];

function generateRows(count) {
    const tableBody = document.getElementById('tableBody');
    let html = "";

    for (let i = 1; i <= count; i++) {
        const id = 1000 + i;
        const fname = firstNames[Math.floor(Math.random() * firstNames.length)];
        const lname = lastNames[Math.floor(Math.random() * lastNames.length)];
        const city = locations[Math.floor(Math.random() * locations.length)];
        const status = Math.random() > 0.2 ? "ACTIVE" : "INACTIVE";
        
        html += `
            <tr>
                <td><span class="status-badge ${status.toLowerCase()}">${status}</span></td>
                <td>${id}</td>
                <td>${fname} ${lname}</td>
                <td>RVM-LP${Math.floor(Math.random() * 50)}-NP${Math.floor(Math.random() * 5)}</td>
                <td>Building ${i}, ${city} St.</td>
                <td>${[35, 50, 75][Math.floor(Math.random() * 3)]}mb-1000</td>
                <td>2026-0${Math.floor(Math.random() * 3) + 1}-15</td>
                <td>0917-${Math.floor(1000000 + Math.random() * 9000000)}</td>
                <td>${Math.floor(Math.random() * 40) + 18}</td>
                <td>${Math.random() > 0.5 ? 'M' : 'F'}</td>
                <td>${fname.toLowerCase()}_fb</td>
                <td>N/A</td>
                <td>19${Math.floor(70 + Math.random() * 28)}-05-12</td>
                <td>${city}</td>
                <td>${Math.floor(Math.random() * 20)}</td>
                <td>${Math.floor(Math.random() * 10)}</td>
                <td>${Math.floor(Math.random() * 200)}m</td>
                <td>${Math.floor(Math.random() * 10)}</td>
                <td>${Math.floor(Math.random() * 20)}</td>
                <td>${Math.floor(Math.random() * 5)}</td>
                <td>N/A</td>
                <td>Installer Name</td>
            </tr>
        `;
    }
    tableBody.innerHTML = html;
    document.getElementById('rowCount').innerText = `${count} Records Loaded`;
}

function filterTable() {
    let input = document.getElementById("tableSearch");
    let filter = input.value.toUpperCase();
    let tr = document.getElementById("tableBody").getElementsByTagName("tr");

    for (let i = 0; i < tr.length; i++) {
        tr[i].style.display = (tr[i].textContent || tr[i].innerText).toUpperCase().indexOf(filter) > -1 ? "" : "none";
    }
}

// Initial Load
window.onload = () => generateRows(2000);