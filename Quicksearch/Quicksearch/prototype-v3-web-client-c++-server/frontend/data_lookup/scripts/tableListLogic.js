

/* ============================================================
    2. VIEW CONTROLLER (Template Loading)
============================================================ */
function loadTemplates(templateId) {

    // kills spelling correction that pesky red line squigles
    document.querySelectorAll('[contenteditable]').forEach(el => {
        el.setAttribute('spellcheck', 'false');
    });

    let container = document.getElementById('app-container');
    let template = document.getElementById(templateId);

    if (template === null) return;

    container.innerHTML = '';
    let instance = template.content.cloneNode(true);
    container.appendChild(instance);

    // Dynamic Sidebar State Management
    let navItems = document.querySelectorAll('.nav-item');
    navItems.forEach(item => {
        item.classList.remove('active');
        
        // Extract the keywords (e.g., 'list', 'profile', 'history')
        let text = item.innerText.toLowerCase();
        
        // If the template ID (view-payment-history) contains the word 'history'
        if (templateId.toLowerCase().includes(text.split(' ')[text.split(' ').length - 1])) {
            item.classList.add('active');
        }
    });
}

/* ============================================================
    3. DATA FETCHING (C++ Backend Interaction)
============================================================ */

function renderTableRows(dataList) {
    const tableBody = document.getElementById("tableBody");
    const customerTable = document.getElementById("customerTable");

    /* CLEAR OLD */
    tableBody.textContent = "";

    /* ALLOW TABLE TO EXPAND */
    customerTable.style.width = "max-content";
    customerTable.style.minWidth = "100%";

    const fragment = document.createDocumentFragment();

    for (let i = 0; i < dataList.length; i++) {
        const c = dataList[i];
        const row = document.createElement("tr");

        // ─── STATUS BADGE LOGIC ───
        const currentStatus = (c.STATUS ?? "").toUpperCase().trim(); 
        let badgeClass = "";

        if (currentStatus === "CURRENT") {
            badgeClass = "badge-current";
        } else if (currentStatus === "DELIQUENT") {
            badgeClass = "badge-delinquent";
        } else if (currentStatus === "DISCONNECTED") {
            badgeClass = "badge-disconnected";
        }  else if (currentStatus === "PULL-OUT") {
            badgeClass = "badge-pull-out";
        } else {
            badgeClass = "badge-default"; // Fallback for empty or unknown statuses
        }
        // ──────────────────────────

        row.innerHTML = `
            <td>
                <button class="delete-btn" data-id="${c.ID}">
                    <img src="../assets/trasbhin.png">
                </button>
            </td>

            <!-- Applied the badge class directly to a span container inside the TD -->
            <td><span class="status-badge ${badgeClass}">${c.STATUS ?? ""}</span></td>
            
            <td>${c.ID ?? ""}</td>
            <td>${c.CLIENTS_NAME ?? ""}</td>
            <td>${c.CREDENTIALS ?? ""}</td>
            <td>${c.ADDRESS ?? ""}</td>
            <td>${c.PLAN ?? ""}</td>
            <td>${c.DATE_APPLIED ?? ""}</td>
            <td>${c.CONTACT_NO ?? ""}</td>
            <td>${c.AGE ?? ""}</td>
            <td>${c.SEX ?? ""}</td>
            <td>${c.SOCIAL_MEDIA ?? ""}</td>
            <td>${c.OCCUPATION ?? ""}</td>
            <td>${c.DATE_OF_BIRTH ?? ""}</td>
            <td>${c.PLACE_OF_BIRTH ?? ""}</td>
            <td>${c.OPTICAL_INFO ?? ""}</td>
            <td>${c.SC_CONNECTOR ?? ""}</td>
            <td>${c.FIBER_DROP ?? ""}</td>
            <td>${c.TAPPING_CLIP ?? ""}</td>
            <td>${c.CABLE_TIE ?? ""}</td>
            <td>${c.F_CLAMP ?? ""}</td>
            <td>${c.REMARKS ?? ""}</td>
            <td>${c.INSTALLED_BY ?? ""}</td>
        `;

        fragment.appendChild(row);
    }

    tableBody.appendChild(fragment);

    document.getElementById("rowCount").textContent =
        `${dataList.length} Records Loaded`;
}

/* ============================================================
    5. SEARCH LOGIC (Imperative Logic)
============================================================ */
function filterTable() {
    let input = document.getElementById("tableSearch").value.toUpperCase().trim().split(" "); // split into words
    let rows = document.querySelectorAll("#tableBody tr");
    let count = 0;

    rows.forEach(row => {

        let text = row.textContent.toUpperCase();
        let match = input.every(word => text.includes(word));

        if (match) { row.style.display = ""; count++;
        } else { row.style.display = "none"; }
    });

    document.getElementById('rowCount').innerText = count + " Records Found";
}

// Entry Point
window.onload = function() {
    loadTemplates('view-client-list');   
    fetchClientmasterList();
};