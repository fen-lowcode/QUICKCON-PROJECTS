
async function hashString(message) {
    // 1. Encode the string as a Uint8Array
    const msgBuffer = new TextEncoder().encode(message);

    // 2. Hash the message using SHA-256
    const hashBuffer = await crypto.subtle.digest('SHA-256', msgBuffer);

    // 3. Convert ArrayBuffer to a hex string
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
    
    return hashHex;
}

document.getElementById('loginForm').addEventListener('submit', async (e) => {
    e.preventDefault(); // Prevents page reload

    // Get the values from the inputs
    const userName = document.getElementById("uname").value;
    const passBuf = document.getElementById("psw").value;
    const password = await hashString(passBuf);

    try {
        const response = await fetch('http://127.0.0.1:2222/auth/session', {
            method: 'POST',
            headers: { 
                'Content-Type': 'application/json',
            },
            
            body: JSON.stringify({ 
                uname: userName, 
                psw: password 
            })
        });

    
        if(response.ok){ var data = await response.json(); console.log(data)}
        

    } catch (error) {
        console.error("Failed to connect to backend:", error);
        alert("Error: Could not reach the backend server.");
    }
});