document.getElementById('loginForm').addEventListener('submit', async (e) => {
    e.preventDefault(); // Prevents page reload

    // Get the values from the inputs
    const firstName = document.getElementById("fname").value;
    const lastName = document.getElementById("lname").value;
    const password = document.getElementById("psw").value;

    try {
        const response = await fetch('http://127.0.0.1:2222/auth/session', {
            method: 'POST',
            headers: { 
                'Content-Type': 'application/json' 
            },
            
            body: JSON.stringify({ 
                fname: firstName, 
                lname: lastName, 
                psw: password 
            })
        });

    
        if(response.ok){ var data = await response.json(); console.log(data)}
        

    } catch (error) {
        console.error("Failed to connect to backend:", error);
        alert("Error: Could not reach the backend server.");
    }
});