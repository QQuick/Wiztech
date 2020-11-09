for (int iStart = 0; iStart < nrOfVertices; iStart++) {
    for (int iEnd = 0; iEnd < nrOfVertices; iEnd++) {
        for (int iVia = 0; iVia < nrOfVertices; iVia++) {
            connectivityMatrix [iStart][iEnd] = min (
                connectivityMatrix [iStart][iEnd],
                connectivityMatrix [iStart, iVia] + connectivityMatrix [iVia, iEnd]
            );
        }
    }
}
