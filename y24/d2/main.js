const fs = require('fs');
const readline = require('readline');

async function parseFile(filePath) {
    try {
        // Create a readable stream
        const fileStream = fs.createReadStream(filePath);

        // Use readline to process the file line by line
        const rl = readline.createInterface({
            input: fileStream,
            crlfDelay: Infinity, // Handles \r\n and \n line endings
        });


	var safe = 0;

        for await (const line of rl) {
            // Split the line into numbers
            	const numbers = line.trim().split(/\s+/).map(Number);
		var overall = false;
		for (var j = -1; j < numbers.length; j++) {
			const num = [];
			for (var i = 0; i < numbers.length; i++) {
				if (i != j) {
					num.push(numbers[i]);
				}
			}

			
		var test = true;
		var inc;
		for (var i = 1; i < num.length; i++) {
			if (Math.abs(num[i-1] - num[i]) > 3 || num[i-1] - num[i] == 0) test = false;
			if (i == 1) {
				inc = num[i] > num[i-1];
			} else if (num[i-1] < num[i] != inc) test = false;
		}
		if (test) overall = true;

		}
		if (overall) safe++;
        }
	console.log(safe);
    } catch (error) {
        console.error(`Error reading the file: ${error.message}`);
    }
}

// Call the function with the file path
parseFile('./input.txt');

