def recursivelyFlipFacets (flipFacet, flipIt):
    flipFacetColorIndex = flipFacet.normalColorIndex if flipFacet.markColorIndex == -1 else flipFacet.markColorIndex
    if flipIt:
        flipFacet.vertices = (flipFacet.vertices [1], flipFacet.vertices [0], flipFacet.vertices [2])
    flipFacet.flipChecked = True
    neighbourCount = 0
    for facet in facets:
        facetColorIndex = facet.normalColorIndex if facet.markColorIndex == -1 else facet.markColorIndex
        if facetColorIndex == flipFacetColorIndex:                                                                              # Same color
            intersection = set (facet.vertices) & set (flipFacet.vertices)
            if len (intersection) > 1:                                                                                          # Edge in common
                neighbourCount += 1
                if not facet.flipChecked:                                                                                       # Meaning not yet handled, keep name for backward compatibility
                    orderedIntersection = tuple (intersection)
                    flipNext =  (
                        (facet.vertices.index (orderedIntersection [1]) - facet.vertices.index (orderedIntersection [0])) % 3 ==
                        (flipFacet.vertices.index (orderedIntersection [1]) - flipFacet.vertices.index (orderedIntersection [0])) % 3
                    )                                                                                                           # Common edge has same vertex order, so opposite orientation
                    recursivelyFlipFacets (facet, flipNext)
        if neighbourCount > 4:                                                                                                  # All neighbours of current flipFacet incl. flipFacet itself were tested
            break                                                                                                               # Waste of time to search for more neighbours
