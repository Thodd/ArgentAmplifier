template <int NumVoices> struct distortion
{
	SNEX_NODE(distortion);
	
	static const int NUM_CHANNELS = 2;
	
	// SNEX has a special float object that handles automatic smoothing
	// they are stateful, so we need two of them for stereo operations
	span<sfloat, NUM_CHANNELS> k;
	
	float getSample(float x, float ck)
	{
			
	        x = x * 0.25f;
	        float a = Math.abs (x);
	        float x2 = x * x;
	        float y = 1.0 - 1.0 / (1.0 + a + x2 + 0.66422417311781f * x2 * a + 0.36483285408241f * x2 * x2);
	        return (x >= 0) ? y : -1.0 * y;

		//return (1.0f + ck) * input / (1.0f + ck * Math.abs(input));
	}
	
	
	template <typename T> void process(T& data)
	{
		const int numChannels = Math.min(data.getNumChannels(), NUM_CHANNELS);
		
		for(int i = 0; i < numChannels; i++)
		{
			for(auto& s: data[i])
			{
				s = getSample(s, k[i].advance());
			}
		}
		

	}
	template <typename T> void processFrame(T& data)
	{
		int i = 0;

		for(auto& s: data)
			s = getSample(s, k[i++].advance());
	}
	void reset()
	{
		// this resets the smoothing and will be called when there
		// needs to be a reininitialisation in the signal stream
		for(auto& ck: k)
			ck.reset();
	}
	
	void prepare(PrepareSpecs ps)
	{
		const double smoothing = 50.0;
		
		for(auto& ck: k)
			ck.prepare(ps.sampleRate, smoothing);
	}
	
	void setExternalData(const ExternalData& d, int index)
	{
	}
	
	template <int P> void setParameter(double v)
	{
		
	}

	// Process the MIDI events here
	void handleHiseEvent(HiseEvent& e)
	{

	}

};
