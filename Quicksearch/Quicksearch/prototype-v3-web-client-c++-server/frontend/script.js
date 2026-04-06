document.getElementById('loginForm').addEventListener('submit', async (e) => {
    e.preventDefault(); // Prevents page reload

    // Get the values from the inputs
    const firstName = document.getElementById("fname").value;
    const lastName = document.getElementById("lname").value;
    const password = document.getElementById("psw").value;

    try {
        const response = await fetch('http://127.0.0.1:9000/auth/session', {
            method: 'POST',
            headers: { 
                'Content-Type': 'application/json' 
            },
            // Match the keys that your nlohmann::json logic expects in C++
            body: JSON.stringify({ 
                fname: firstName, 
                lname: lastName, 
                psw: password 
            })
        });

        if (!response.ok) {
            throw new Error(`Server responded with status: ${response.status}`);
        }

        const data = await response.json();
        alert("Response from C++: " + (data.status || "Success!"));
    } catch (error) {
        console.error("Failed to connect to C++ backend:", error);
        alert("Error: Could not reach the backend.");
    }
});