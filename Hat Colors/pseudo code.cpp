//Algorithm passTest(prisoners)
//Input An Array of 12 Prisoners
//Output An Array of Prisoners who stepped forward in line
//    Max_Black_Hat_Founds <- 0
//
//    for Prisoners_loop <- 0 to 11 do
//        BlackHats_count <- 0
//
//        // Count the number of black hats among other prisoners
//        for scan_loop <- 0 to 11 do
//            if scan_loop ≠ Prisoners_loop and prisoners[scan_loop].hatColor = BLACK then
//                BlackHats_count <- BlackHats_count + 1
//
//        if BlackHats_count > Max_Black_Hat_Founds then
//            Max_Black_Hat_Founds <- BlackHats_count      
//
//        // Case 1: 1 Black Hat
//        if BlackHats_count = 0 then
//            line <- prisoners[Prisoners_loop]
//            return line     
//    
//
//    // Case: More than 1 Black Hat
//     currentLineup <- 1  // Start from the second lineup
//    
//    while currentLineup <= Max_Black_Hat_Founds do
//        // Check subsequent lineups
//        for Prisoners_loop <- 0 to 11 do
//             BlackHatsSeen <- 0
//    
//            // Count the number of black hats seen by this prisoner in the current lineup
//            for scan_loop <- 0 to 11 do
//                if scan_loop ≠ Prisoners_loop and prisoners[scan_loop].hatColor = BLACK then
//                     BlackHatsSeen <- BlackHatsSeen + 1
//        
//                    // Check if the current prisoner can deduce the color of their hat
//            if BlackHatsSeen = currentLineup - 1 then
//                line <- prisoners[Prisoners_loop]
//    
//        currentLineup <- currentLineup + 1
//    
//    return line