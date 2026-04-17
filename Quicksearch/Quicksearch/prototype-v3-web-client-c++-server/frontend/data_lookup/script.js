/* ============================================================
    1. CORE UTILITIES (The "Pointers" & "Sanity Checks")
============================================================ */

// Helper to write data to the DOM. Checks if ID exists before writing.
function writeToUI(elementId, value) {
    let target = document.getElementById(elementId);
    if (target !== null) {
        // If value is null or empty, use a placeholder
        if (value === undefined || value === null || value === "") {
            target.innerText = "---";
        } else {
            target.innerText = value;
        }
    }
}

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
    let tableBody = document.getElementById('tableBody');
    let htmlBuilder = "";

    for (let i = 0; i < dataList.length; i++) {
        let c = dataList[i];
        let stat = c.status || "ACTIVE";
        
        // Build raw HTML string for performance
        htmlBuilder += `
            <tr>
                <td><button class="delete-btn" onclick="deleteCustomer('${c.id}')"><img src="../../assets/trasbhin.png"></button></td>
                <td><span class="status-badge ${stat.toLowerCase()}">${stat}</span></td>
                <td>${c.id}</td><td>${c.name}</td>
                <td>${c.credentials || 'N/A'}</td>
                <td>${c.address}</td>
                <td>${c.plan}</td>
                <td>${c.date_applied}</td>
                <td>${c.contact_no}</td>
                <td>${c.age}</td>
                <td>${c.sex}</td>
                <td>${c.social_media}</td>
                <td>${c.occupation}</td>
                <td>${c.dob}</td>
                <td>${c.pob}</td>
                <td>${c.optical_info}</td>
                <td>${c.sc_connector}</td>
                <td>${c.fiber_drop}</td>
                <td>${c.tapping_clip}</td>
                <td>${c.cable_tie}</td>
                <td>${c.f_clamp}</td>
                <td>${c.remarks}</td>
                <td>${c.installed_by}</td>
            </tr>`;
    }
    tableBody.innerHTML = htmlBuilder;
    document.getElementById('rowCount').innerText = dataList.length + " Records Loaded";
}

/* ============================================================
    4. EVENT HANDLING (The Bridge)
============================================================ */
document.addEventListener('click', function(e) {
    let row = e.target.closest('#tableBody tr');
    let isDelete = e.target.closest('.delete-btn');

    if (row === null || isDelete !== null) return;

    // Extracting data from table columns (Indices match <thead>)
    let cells = row.cells;
    let packet = {
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

    openProfile(packet);
});


function openProfile(data) {
    loadTemplates('view-profile');

    // Header logic
    writeToUI('prof-name-display', data.name);
    let badge = document.getElementById('prof-status-badge');
    if (badge) {
        badge.innerText = data.status;
        badge.className = "status-badge " + data.status.toLowerCase();
    }

    // Direct Mapping to the Template IDs we created
    writeToUI('view-id',      data.id);
    writeToUI('view-plan',    data.plan);
    writeToUI('view-creds',   data.creds);
    writeToUI('view-applied', data.applied);
    writeToUI('view-age',     data.age);
    writeToUI('view-sex',     data.sex);
    writeToUI('view-job',     data.job);
    writeToUI('view-dob',     data.dob);
    writeToUI('view-pob',     data.pob);
    writeToUI('view-address', data.address);
    writeToUI('view-contact', data.contact);
    writeToUI('view-social',  data.social);
    writeToUI('view-optical', data.optical);
    writeToUI('view-tech',    data.tech);
    writeToUI('view-remarks', data.remarks);
    writeToUI('view-sc',      data.sc);
    writeToUI('view-fiber',   data.fiber);
    writeToUI('view-clip',    data.clip);
    writeToUI('view-tie',     data.tie);
    writeToUI('view-fclamp',  data.fclamp);
}

function openHistory(data) {
    loadTemplates('view-payment-history')
}

/* ============================================================
    5. SEARCH LOGIC (Imperative Logic)
============================================================ */
function filterTable() {
    let input = document.getElementById("tableSearch").value.toUpperCase();
    let rows = document.querySelectorAll("#tableBody tr");
    let count = 0;

    for (let i = 0; i < rows.length; i++) {
        let text = rows[i].textContent.toUpperCase();
        if (text.indexOf(input) > -1) {
            rows[i].style.display = "";
            count++;
        } else {
            rows[i].style.display = "none";
        }
    }
    document.getElementById('rowCount').innerText = count + " Records Found";
}

// Entry Point
window.onload = function() {
    loadTemplates('view-client-list');
    fetchClientmasterList();
};